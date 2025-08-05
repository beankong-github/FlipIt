#pragma once
#include "Level/Level.h"
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


private:
	void InitializeTileMap();

private:
	// ∏  ∏Æº“Ω∫
	MapData* mapData;
	// ≈∏¿œ∏ 
	std::vector<std::vector<Tile*>> tileMap;

};