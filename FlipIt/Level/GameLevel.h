#pragma once
#include "Level/Level.h"
#include "Actor/Tile.h"

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	virtual ~GameLevel();

private:
	// ¸Ê ¸®¼Ò½º
};