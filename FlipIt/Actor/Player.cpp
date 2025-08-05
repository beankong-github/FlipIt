#include "Player.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"
#include "Level/GameLevel.h"
#include "Actor/Outliner.h"
#include "Engine.h"
#include <cassert>


const Vector2 Player::directions[(int)EDirection::MAX] = { Vector2(0,-1), Vector2(0,1), Vector2(-1,0), Vector2(1,0) };

Player::Player(const char* image, Vector2 startPosIndex, EDirection startDir, ETileState targetTile)
	:playerTileState(targetTile), positionIndex(startPosIndex), curDir(startDir)
{
	// 이미지 데이터 가져오기
	imageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, image));
	
	// TODO imageData가 없을 때 처리
	assert(imageData != nullptr);

	// 크기 설정
	SetSize(imageData->Size());

	// 이미지 복사
	//// 문자열 길이.
	//length = (int)strlen(tileImageData->Buffer());
	//// 메모리 할당.
	//this->image = new char[length + 1];
	//// 문자열 복사.
	//strcpy_s(this->image, length + 1, tileImageData->Buffer());


	//tmp
	sortingOrder = 3;
	color = EColor::Red;
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	// 위치 설정
	SetPositionOnTile(positionIndex);

}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// tmp 종료 처리. 종료처리는 level에서 한다.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
		return;
	}

	// tmp 입력처리 
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		Move(EDirection::Right);
	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		Move(EDirection::Left);
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		Move(EDirection::Up);
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		Move(EDirection::Down);
	}

	if (SelectableTileOutliner != nullptr)
	{
		if (SelectableTileOutliner->IsActive() && Input::Get().GetKeyDown(VK_SPACE))
		{
 			GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
			// Player가 속한 레벨이 gamelevel이 아닐 경우 assert 
			assert(gameLevel);

			if (gameLevel->FlipTile(selectedTileIndex, playerTileState))
			{
				SelectableTileOutliner->DeactivateOutliner();
			}
		}
	}
}

void Player::Render()
{
	Engine::Get().WriteToBuffer(*this);
}

inline const char* Player::Image() const
{
	// imageData가 있는 경우는 Buffer를 반환한다.
	if(imageData != nullptr)
		return imageData->Buffer();
	return image;
}

void Player::Move(EDirection moveDir)
{
	// 기존에 선택되어 있던 타일이 있다면 선택을 해제한다.
	if (SelectableTileOutliner != nullptr && SelectableTileOutliner->IsActive())
	{
		SelectableTileOutliner->DeactivateOutliner();
	}

	// 방향이 유효하지 않는 경우 이동하지 않는다
	if (moveDir == EDirection::None || moveDir == EDirection::MAX)
		return;



	// 특정 방향으로 이동한다.
	SetPositionOnTile(positionIndex + directions[(int)moveDir]);
}

void Player::SetPositionOnTile(Vector2 newPosition)
{
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
	// Player가 속한 레벨이 gamelevel이 아닐 경우 assert 
	assert(gameLevel);
	

	// 1. 새로운 위치가 타일 범위 내인지 확인
	Vector2 size = gameLevel->GetTilMapSize();
	if ( newPosition.x < 0 || newPosition.x >= size.x
		|| newPosition.y < 0|| newPosition.y >= size.y)
		return;

	// 2. 이동할 위치의 타일 확인하기
	ETileState tileState = gameLevel->GetTileState(newPosition);
	// 만약 이동하려고 했던 타일이 상대 타일이었다면 선택한다.
	if(tileState == REVERSE(playerTileState))
	{
		SelectTile(newPosition);
		return;
	}

	if (tileState == playerTileState)
	{
		// 이동!
		positionIndex = newPosition;


		// 화면상의 position 계산하기(타일 중앙에 오도록)
		// 타일 포지션 + (타일 크기 - 액터 크기) / 2
		Vector2 offset = gameLevel->GetTileSize(positionIndex) - imageData->Size();
		offset.x = offset.x < 0 ? 0 : offset.x;
		offset.y = offset.y < 0 ? 0 : offset.y;

		position = gameLevel->GetTileConsolePos(positionIndex) + (offset / 2);
	}
}

void Player::SelectTile(Vector2 tile)
{
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
	// Player가 속한 레벨이 gamelevel이 아닐 경우 assert 
	assert(gameLevel);

	selectedTileIndex = tile;

	// 아웃라이너가 없으면 생성한다
	if (SelectableTileOutliner == nullptr)
	{
		// tmp 아웃라이더 데이터 값 바로 전달
		SelectableTileOutliner = new Outliner("Outliner.txt");
		assert(SelectableTileOutliner);
		owner->AddActor(SelectableTileOutliner);
	}
	SelectableTileOutliner->ActivateOutliner(gameLevel->GetTileConsolePos(selectedTileIndex), EColor::None, color);

}
