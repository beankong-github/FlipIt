#include "Game.h"
#include "Level/TestLevel.h"
#include "ResourceMgr.h"

Game::Game()
	:Engine()
{
	AddLevel(new TestLevel());
	ResourceManager = new ResourceMgr();
}

void Game::CleanUp()
{
	Super::CleanUp();
	SafeDelete(ResourceManager);
}

Game::~Game()
{
	CleanUp();
}
