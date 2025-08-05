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
	// �̹��� ������ ��������
	imageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, image));
	
	// TODO imageData�� ���� �� ó��
	assert(imageData != nullptr);

	// ũ�� ����
	SetSize(imageData->Size());

	// �̹��� ����
	//// ���ڿ� ����.
	//length = (int)strlen(tileImageData->Buffer());
	//// �޸� �Ҵ�.
	//this->image = new char[length + 1];
	//// ���ڿ� ����.
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

	// ��ġ ����
	SetPositionOnTile(positionIndex);

}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// tmp ���� ó��. ����ó���� level���� �Ѵ�.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
		return;
	}

	// tmp �Է�ó�� 
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
			// Player�� ���� ������ gamelevel�� �ƴ� ��� assert 
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
	// imageData�� �ִ� ���� Buffer�� ��ȯ�Ѵ�.
	if(imageData != nullptr)
		return imageData->Buffer();
	return image;
}

void Player::Move(EDirection moveDir)
{
	// ������ ���õǾ� �ִ� Ÿ���� �ִٸ� ������ �����Ѵ�.
	if (SelectableTileOutliner != nullptr && SelectableTileOutliner->IsActive())
	{
		SelectableTileOutliner->DeactivateOutliner();
	}

	// ������ ��ȿ���� �ʴ� ��� �̵����� �ʴ´�
	if (moveDir == EDirection::None || moveDir == EDirection::MAX)
		return;



	// Ư�� �������� �̵��Ѵ�.
	SetPositionOnTile(positionIndex + directions[(int)moveDir]);
}

void Player::SetPositionOnTile(Vector2 newPosition)
{
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
	// Player�� ���� ������ gamelevel�� �ƴ� ��� assert 
	assert(gameLevel);
	

	// 1. ���ο� ��ġ�� Ÿ�� ���� ������ Ȯ��
	Vector2 size = gameLevel->GetTilMapSize();
	if ( newPosition.x < 0 || newPosition.x >= size.x
		|| newPosition.y < 0|| newPosition.y >= size.y)
		return;

	// 2. �̵��� ��ġ�� Ÿ�� Ȯ���ϱ�
	ETileState tileState = gameLevel->GetTileState(newPosition);
	// ���� �̵��Ϸ��� �ߴ� Ÿ���� ��� Ÿ���̾��ٸ� �����Ѵ�.
	if(tileState == REVERSE(playerTileState))
	{
		SelectTile(newPosition);
		return;
	}

	if (tileState == playerTileState)
	{
		// �̵�!
		positionIndex = newPosition;


		// ȭ����� position ����ϱ�(Ÿ�� �߾ӿ� ������)
		// Ÿ�� ������ + (Ÿ�� ũ�� - ���� ũ��) / 2
		Vector2 offset = gameLevel->GetTileSize(positionIndex) - imageData->Size();
		offset.x = offset.x < 0 ? 0 : offset.x;
		offset.y = offset.y < 0 ? 0 : offset.y;

		position = gameLevel->GetTileConsolePos(positionIndex) + (offset / 2);
	}
}

void Player::SelectTile(Vector2 tile)
{
	GameLevel* gameLevel = dynamic_cast<GameLevel*>(owner);
	// Player�� ���� ������ gamelevel�� �ƴ� ��� assert 
	assert(gameLevel);

	selectedTileIndex = tile;

	// �ƿ����̳ʰ� ������ �����Ѵ�
	if (SelectableTileOutliner == nullptr)
	{
		// tmp �ƿ����̴� ������ �� �ٷ� ����
		SelectableTileOutliner = new Outliner("Outliner.txt");
		assert(SelectableTileOutliner);
		owner->AddActor(SelectableTileOutliner);
	}
	SelectableTileOutliner->ActivateOutliner(gameLevel->GetTileConsolePos(selectedTileIndex), EColor::None, color);

}
