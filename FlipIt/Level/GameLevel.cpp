#include "GameLevel.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Actor/Tile.h"
#include "Asset/MapData.h"


GameLevel::GameLevel(const char* mapName)
{
	// mapData �������� 
	mapData = dynamic_cast<MapData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Map, mapName));
	
	// TODO -> mapName�� ��ȿ���� �ʾ��� ��� ó��
	assert(mapData != nullptr);
	
	InitializeTileMap();
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
