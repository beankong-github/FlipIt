#include "Game.h"
#include "Level/TestLevel.h"
#include "Level/GameLevel.h"
#include "ResourceMgr.h"
#include "TextImageRenderer.h"

Game::Game()
	:Engine()
{
	resourceMgr = new ResourceMgr();
	textImageRenderer = new TextImageRenderer();

	AddLevel(new GameLevel("AITestMap.txt"));
}

void Game::CleanUp()
{
	Super::CleanUp();
	SafeDelete(resourceMgr);
	SafeDelete(textImageRenderer);
}

Game::~Game()
{
	CleanUp();
}
