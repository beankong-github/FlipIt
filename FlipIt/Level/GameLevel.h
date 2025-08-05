#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
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

	const std::vector<std::vector<Tile*>> TileMap() const { return tileMap; };
	Vector2 GetTilMapSize() const;
	ETileState GetTileState(Vector2 index) const;

private:
	void InitializeTileMap();

private:
	// ∏  ∏Æº“Ω∫
	MapData* mapData;
	// ≈∏¿œ∏ 
	std::vector<std::vector<Tile*>> tileMap;

};