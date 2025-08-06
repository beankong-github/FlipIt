#include "GameLevel.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/MapData.h"
#include "Actor/Tile.h"
#include "Actor/Player.h"
#include "Actor/EnemyAI.h"
#include "Game/TextImageRenderer.h"


GameLevel::GameLevel(const char* mapName)
{
	// mapData 가져오기 
	mapData = dynamic_cast<MapData*>(Game::Get().GetResourceMgr()->GetResource(EResourceType::Map, mapName));
	
	// TODO -> mapName이 유효하지 않았을 경우 처리
	assert(mapData != nullptr);
	
	// 맵 위치 offset 계산 
	mapPositionOffset.x = 10 + ((Game::Get().Width()/2) - (mapData->MapSize().x)) /2;
	mapPositionOffset.y = 15;

	// 게임 시간 초기화
	remainTime = gameTime;

	// 타일맵 초기화
	InitializeTileMap();

	// 액터 추가
	AddActor(new Player("Player.txt", Vector2(7, 5), EDirection::Right, ETileState::Front));
	AddActor(new EnemyAI("Player.txt", Vector2(0, 0), EDirection::Right, ETileState::Back));
	//AddActor(new Player("Player.txt", Vector2(0, 1), EDirection::Right, ETileState::Back));
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	Super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{

	if (remainTime <= 0)
	{
		return;
		// 결과창


		CheckScore();

	}


	Super::Tick(deltaTime);
	
	remainTime -= deltaTime;


}

void GameLevel::Render()
{
	// 화면 상단에 남은 시간 렌더링
	RenderGameTimer();

	Super::Render();
}

void GameLevel::RenderGameTimer()
{
	std::string remainTimeString;
	Vector2 textPos;
	EColor textColor = EColor::White;

	std::string min = std::to_string(static_cast<int>(remainTime / 60));
	std::string sec = std::to_string(static_cast<int>(remainTime) % 60);
	if (min.size() == 1)
		min = '0' + min;
	if (sec.size() == 1)
		sec = '0' + sec;
	remainTimeString = min + ":" + sec;

	textPos.x = (Game::Get().Width() / 2) - ((remainTimeString.size() * 4));
	textPos.y = 3;
	
	if (remainTime <= 11)
	{
		textColor = EColor::Yellow;
		if(remainTime <= 4)
			textColor = EColor::Red;
	}

	Game::Get().GetTextImageRenderer()->RenderText(remainTimeString.c_str(), textPos, textColor, EColor::None, 10, EFont::Timer);
}

void GameLevel::Pause()
{
	isPause = true;
}

void GameLevel::Play()
{
	isPause = false;
}

const Tile& GameLevel::GetTile(Vector2 index) const
{
	// Tile에 const를 붙여 반환한다.
	return *const_cast<Tile*>(GetTileInternal(index));
}

Vector2 GameLevel::GetTilMapSize() const
{
	if (mapData != nullptr)
	{
		return mapData->MapSize();
	}
	return Vector2();
}

Vector2 GameLevel::GetTileSize(Vector2 index) const
{
	const Tile* tile = GetTileInternal(index);

	if (tile != nullptr)
		return tile->Size();

	return Vector2();
}

Vector2 GameLevel::GetTileConsolePos(Vector2 index) const
{
	const Tile* tile = GetTileInternal(index);

	if (tile != nullptr)
		return tile->Position();

	return Vector2();
}

ETileState GameLevel::GetTileState(Vector2 index) const
{
	const Tile* tile= GetTileInternal(index);

	if (tile != nullptr)
		return tile->TileState();

	return ETileState::None;
}

void GameLevel::OnPlayerMove(Vector2 prevPos, Vector2 newPos, ETileState state)
{
	Tile* prevTile = GetTileInternal(prevPos);
	assert(prevTile != nullptr);
	prevTile->OnPlayerLeave(state);

	Tile* newTile = GetTileInternal(newPos);
	assert(newTile != nullptr);
	newTile->OnPlayerCome();
}

EColor GameLevel::GetTileBackgroundColor(Vector2 index) const
{
	const Tile* tile = GetTileInternal(index);

	if (tile != nullptr)
		return tile->BackgroundColor();

	return EColor();
}

bool GameLevel::FlipTile(Vector2 index, ETileState state)
{
	// TODO 타일을 뒤집기 전에 조건 확인
	// 아이템이 있다거나
	// 시간이 다됐거나
	// 게임이 종료될 예정이라던가 -> 상관 없을듯?	

	Tile* tile = GetTileInternal(index);
	if (tile->TileState() == ETileState::None || tile->TileState() == ETileState::Block)
		return false;

	if (tile != nullptr)
	{
		tile->Flip(state);
		CheckScore();
		return true;
	}
	return false;
}

void GameLevel::CheckScore()
{
	// 점수 계산
	for (const auto& tiles : tileMap)
	{
		for (const auto& tile : tiles)
		{
			if (tile->TileState() == ETileState::Front)
				++scoreFront;

			if (tile->TileState() == ETileState::Back)
				++scoreBack;
		}
	}

	++scoreFront;		// front actor가 서있는 위치 계산
	++scoreBack;		// back actor가 서있는 위치 계산
}

void GameLevel::InitializeTileMap()
{
	// mapData를 기반으로 타일 Actor 생성
	if (mapData != nullptr)
	{
		const Vector2 mapSize = mapData->MapSize();
		for (int iy = 0; iy < mapSize.y; ++iy)
		{
			tileMap.emplace_back(std::move(std::vector<Tile*>()));
			for (int ix = 0; ix < mapSize.x; ++ix)
			{
				// 타일 생성
				Tile* tile = new Tile((*mapData)[iy][ix], Vector2(ix, iy));
				tile->SetPositionOffset(mapPositionOffset);
				// 액터로 추가함
				AddActor(tile);
				// 타일맵에 타일 추가
				tileMap[iy].emplace_back(tile);
			}
		}
	}
}

Tile* GameLevel::GetTileInternal(Vector2 index) const
{
	if (index.x < 0 || index.x >= GetTilMapSize().x 
		|| index.y < 0||index.y >= GetTilMapSize().y)
		return nullptr;

	return tileMap[index.y][index.x];
}
