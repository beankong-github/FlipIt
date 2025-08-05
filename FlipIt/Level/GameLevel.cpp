#include "GameLevel.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/MapData.h"
#include "Actor/Tile.h"
#include "Actor/Player.h"


GameLevel::GameLevel(const char* mapName)
{
	// mapData 가져오기 
	mapData = dynamic_cast<MapData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Map, mapName));
	
	// TODO -> mapName이 유효하지 않았을 경우 처리
	assert(mapData != nullptr);
	
	InitializeTileMap();

	AddActor(new Player("Player.txt", Vector2(0, 0), EDirection::Right));
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
	Super::Tick(deltaTime);
}

void GameLevel::Render()
{
	Super::Render();
}

Vector2 GameLevel::GetTilMapSize() const
{
	if (mapData != nullptr)
	{
		return mapData->MapSize();
	}
	return Vector2();
}

ETileState GameLevel::GetTileState(Vector2 index) const
{
	// TODO
	return ETileState();
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
				// 액터로 추가함
				AddActor(tile);
				// 타일맵에 타일 추가
				tileMap[iy].emplace_back(tile);
			}
		}
	}
}
