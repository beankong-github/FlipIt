#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Game/Types.h"
#include <vector>

class MapData;
class Tile;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(const char* mapName);
	virtual ~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

	void RenderGameTimer();

	void Pause();
	void Play();
	
	// Tile 
	const std::vector<std::vector<Tile*>>& TileMap() const { return tileMap; };
	const Tile& GetTile(Vector2 index) const;
	Vector2 GetTilMapSize() const;
	Vector2 GetTileSize(Vector2 index) const;
	Vector2 GetTileConsolePos(Vector2 index) const;
	EColor GetTileBackgroundColor(Vector2 index) const;
	bool FlipTile(Vector2 index, ETileState state);
	void CheckScore();
	ETileState GetTileState(Vector2 index) const;

	// 플레이어가 자신의 현재 위치의 타일 상태를 변경할때만 사용한다. 그 외는 사용에 주의한다.
	void OnPlayerMove(Vector2 prevPos, Vector2 newPos, ETileState state);

private:
	void InitializeTileMap();
	Tile* GetTileInternal(Vector2 index) const;


private:
	bool isPause;

	// ==== TileMap ============
	// 맵 리소스
	MapData* mapData;
	// 타일맵
	std::vector<std::vector<Tile*>> tileMap;
	// 타일맵 위치
	Vector2 mapPositionOffset;

	// ==== Game Time ============
	unsigned int gameTime = 15;
	float remainTime = 0;


	// ==== Game Rule ============
	int scoreFront = 0;
	int scoreBack = 0;
	
	// ==== Actor - UI ============
	class UI* gameOverUI;


	// ==== Actor - U ============
	class Player* playerFront;
	class Player* playerBack;
};