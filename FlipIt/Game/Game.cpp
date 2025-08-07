#include "Game.h"
#include "Level/TestLevel.h"
#include "Level/GameLevel.h"
#include "Level/ResultLevel.h"
#include "ResourceMgr.h"
#include "Utils/Utils.h"
#include "TextImageRenderer.h"

Game::Game()
	:Engine()
{
	resourceMgr = new ResourceMgr();
	textImageRenderer = new TextImageRenderer();

	//AddLevel(new GameLevel("AITestMap.txt"));
	StartGame();
}

void Game::CleanUp()
{
	Super::CleanUp();
	SafeDelete(resourceMgr);
	SafeDelete(textImageRenderer);
}

void Game::StartGame()
{
	// ·£´ý ¸Ê
	auto resourceMap =  resourceMgr->GetReosurceHashMap(EResourceType::Map);
	auto random_it = std::next(resourceMap->begin(), Utils::Random(0, resourceMap->size()-1));
	AddLevel(new GameLevel(random_it->first.c_str()));
}

void Game::FinishGame(int playerScore, int enemyScore)
{
	ResultLevel* resultLevel = new ResultLevel;
	if(resultLevel)
		resultLevel->SetScore(playerScore, enemyScore);

	AddLevel(resultLevel);
}

Game::~Game()
{
	CleanUp();
}
