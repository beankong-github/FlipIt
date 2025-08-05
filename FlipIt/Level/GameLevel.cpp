#include "GameLevel.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/MapData.h"
#include "Actor/Tile.h"
#include "Actor/Player.h"


GameLevel::GameLevel(const char* mapName)
{
	// mapData �������� 
	mapData = dynamic_cast<MapData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Map, mapName));
	
	// TODO -> mapName�� ��ȿ���� �ʾ��� ��� ó��
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
	// mapData�� ������� Ÿ�� Actor ����
	if (mapData != nullptr)
	{
		const Vector2 mapSize = mapData->MapSize();
		for (int iy = 0; iy < mapSize.y; ++iy)
		{
			tileMap.emplace_back(std::move(std::vector<Tile*>()));
			for (int ix = 0; ix < mapSize.x; ++ix)
			{
				// Ÿ�� ����
				Tile* tile = new Tile((*mapData)[iy][ix], Vector2(ix, iy));
				// ���ͷ� �߰���
				AddActor(tile);
				// Ÿ�ϸʿ� Ÿ�� �߰�
				tileMap[iy].emplace_back(tile);
			}
		}
	}
}
