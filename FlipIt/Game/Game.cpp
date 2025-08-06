#include "Game.h"
#include "Level/TestLevel.h"
#include "Level/GameLevel.h"
#include "ResourceMgr.h"

Game::Game()
	:Engine()
{
	resourceManager = new ResourceMgr();

	AddLevel(new GameLevel("AITestMap.txt"));
}

void Game::CleanUp()
{
	Super::CleanUp();
	SafeDelete(resourceManager);
}

Game::~Game()
{
	CleanUp();
}
