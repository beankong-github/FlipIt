#include "GameLevel.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/MapData.h"
#include "Actor/Tile.h"
#include "Actor/Player.h"
#include "Actor/EnemyAI.h"
#include "Game/TextImageRenderer.h"
#include "Level/ResultLevel.h"


GameLevel::GameLevel(const char* mapName)
{
	// mapData �������� 
	mapData = dynamic_cast<MapData*>(Game::Get().GetResourceMgr()->GetResource(EResourceType::Map, mapName));
	
	// TODO -> mapName�� ��ȿ���� �ʾ��� ��� ó��
	assert(mapData != nullptr);
	
	// �� ��ġ offset ��� 
	mapPositionOffset.x = 10 + ((Game::Get().Width()/2) - (mapData->MapSize().x)) /2;
	mapPositionOffset.y = 15;

	// ���� �ð� �ʱ�ȭ
	remainTime = gameTime;

	// Ÿ�ϸ� �ʱ�ȭ
	InitializeTileMap();

	// ���� �߰�
	AddActor(new Player("Player.txt", mapData->PlayerSpawnPos(), EDirection::Right, ETileState::Front));
	AddActor(new EnemyAI("Player.txt", mapData->EnemySpawnPos(), EDirection::Right, ETileState::Back));
	//AddActor(new Player("Player.txt", Vector2(0, 1), EDirection::Right, ETileState::Back));
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	Super::BeginPlay();

	CheckScore();
}

void GameLevel::Tick(float deltaTime)
{
#ifdef _DEBUG
	if (Input::Get().GetKeyDown(VK_BACK))
	{
		remainTime = 0;
	}
#endif
	
	QuitGame();

	if (remainTime <= 0)
	{
		CheckScore();
		// tmp �ƴ� �� ���� ������ �������� �ٴ޶� ���ƾ�????????
		Game::Get().FinishGame(scoreFront, scoreBack);
		return;
	}

	Super::Tick(deltaTime);
	remainTime -= deltaTime;
}

void GameLevel::Render()
{
	// ȭ�� ��ܿ� ���� �ð� ������
	RenderGameTimer();

	// ���� ������
	// Player
	Game::Get().GetTextImageRenderer()->RenderText("Player", Vector2( 5, mapPositionOffset.y), EColor::LightBlue, EColor::None, 10, EFont::Text);
	Game::Get().GetTextImageRenderer()->RenderText("score", Vector2( 5, mapPositionOffset.y+5), EColor::White, EColor::None, 10, EFont::Text);
	
	std::string playerScore = std::to_string(scoreFront);
	Game::Get().GetTextImageRenderer()->RenderText(playerScore.c_str(), Vector2(15, mapPositionOffset.y + 15), EColor::LightBlue, EColor::None, 10, EFont::Timer);


	// ��
	Game::Get().GetTextImageRenderer()->RenderText("Enemy", Vector2(Engine::Get().Width()-45, mapPositionOffset.y), EColor::Red, EColor::None, 10, EFont::Text);
	Game::Get().GetTextImageRenderer()->RenderText("score", Vector2(Engine::Get().Width() - 45, mapPositionOffset.y + 5), EColor::White, EColor::None, 10, EFont::Text);

	std::string enemyScore = std::to_string(scoreBack);
	Game::Get().GetTextImageRenderer()->RenderText(enemyScore.c_str(), Vector2(Engine::Get().Width() - 35, mapPositionOffset.y + 15), EColor::Red, EColor::None, 10, EFont::Timer);

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
		CheckScore();
		return true;
	}
	return false;
}

void GameLevel::CheckScore()
{
	// ���� ���
	scoreFront = 0;
	scoreBack = 0;
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

	++scoreFront;		// front actor�� ���ִ� ��ġ ���
	++scoreBack;		// back actor�� ���ִ� ��ġ ���
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
				tile->SetPositionOffset(mapPositionOffset);
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
