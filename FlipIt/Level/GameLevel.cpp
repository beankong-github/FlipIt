#include "GameLevel.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/MapData.h"
#include "Actor/Tile.h"
#include "Actor/Player.h"
#include "Actor/EnemyAI.h"


GameLevel::GameLevel(const char* mapName)
{
	// mapData �������� 
	mapData = dynamic_cast<MapData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Map, mapName));
	
	// TODO -> mapName�� ��ȿ���� �ʾ��� ��� ó��
	assert(mapData != nullptr);
	
	InitializeTileMap();

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
	Super::Tick(deltaTime);
}

void GameLevel::Render()
{
	Super::Render();
}

const Tile& GameLevel::GetTile(Vector2 index) const
{
	// Tile�� const�� �ٿ� ��ȯ�Ѵ�.
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
	// TODO Ÿ���� ������ ���� ���� Ȯ��
	// �������� �ִٰų�
	// �ð��� �ٵưų�
	// ������ ����� �����̶���� -> ��� ������?


	Tile* tile = GetTileInternal(index);
	if (tile->TileState() == ETileState::None || tile->TileState() == ETileState::Block)
		return false;

	if (tile != nullptr)
	{
		tile->Flip(state);
		return true;
	}
	return false;
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

Tile* GameLevel::GetTileInternal(Vector2 index) const
{
	if (index.x < 0 || index.x >= GetTilMapSize().x 
		|| index.y < 0||index.y >= GetTilMapSize().y)
		return nullptr;

	return tileMap[index.y][index.x];
}
