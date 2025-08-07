#include "ResultLevel.h"
#include "Game/Game.h"

ResultLevel::ResultLevel()
{
	AddMenuItem("Replay!", []() {Game::Get().StartGame(); });
	AddMenuItem("Exit", []() {Game::Get().Quit(); });
}

void ResultLevel::SetScore(int front, int back)
{ 
	frontScore = front;
	BackScore = back;

	if (frontScore > BackScore)
	{
		title = "You Win!";
	}
	else if (frontScore < BackScore)
	{
		title = "You Lose";
	}
	else
		title = "Awesome! Tied with the enemy!";

}

void ResultLevel::Render()
{
	Super::Render();

}
