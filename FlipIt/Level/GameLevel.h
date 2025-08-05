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
	

	// Tile 
	const std::vector<std::vector<Tile*>> TileMap() const { return tileMap; };
	const Tile& GetTile(Vector2 index) const;
	Vector2 GetTilMapSize() const;
	Vector2 GetTileSize(Vector2 index) const;
	Vector2 GetTilePos(Vector2 index) const;
	ETileState GetTileState(Vector2 index) const;
	bool FlipTile(Vector2 index);

private:
	void InitializeTileMap();
	Tile* GetTileInternal(Vector2 index) const;

private:
	// ∏  ∏Æº“Ω∫
	MapData* mapData;
	// ≈∏¿œ∏ 
	std::vector<std::vector<Tile*>> tileMap;

};