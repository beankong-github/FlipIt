#include "Game.h"
#include "Level/TestLevel.h"

Game::Game()
{
	AddLevel(new TestLevel());
}
