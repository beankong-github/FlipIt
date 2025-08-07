#include "ResultLevel.h"
#include "Game/Game.h"
#include "Game/TextImageRenderer.h"

ResultLevel::ResultLevel()
{
	itemSpace = 10;

	AddMenuItem("Replay!", []() {Game::Get().StartGame(); });
	AddMenuItem("Exit", []() {Game::Get().Quit(); });
}

void ResultLevel::SetScore(int front, int back)
{
	frontScore = front;
	BackScore = back;

	if (frontScore > BackScore)
	{
		isWin = true;
		title = "You Win!";
		context = "";
	}
	else if (frontScore < BackScore)
	{
		isWin = false;
		title = "You Lose";
		context = "";
	}
	else
	{
		isWin = false;
		title = "Awesome!";
		context = "Tied with the enemy!";
	}

}

void ResultLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ResultLevel::Render()
{
	TextImageRenderer* titleRenderer = Game::Get().GetTextImageRenderer();
	assert(titleRenderer);

	//Super::Render();
	EColor color;
	if (frontScore > BackScore)
		color = EColor::LightBlue;
	else
		color = EColor::LightRed;

	Vector2 titlepos;
	titlepos.x = Engine::Get().Width() / 2 - title.length() * 3;
	titlepos.y = 10;
	titleRenderer->RenderText(title.c_str(), titlepos, color, EColor::None, 10);

	Vector2 contextpos;
	contextpos.x = titlepos.x - context.length();
	contextpos.y = 18;
	titleRenderer->RenderText(context.c_str(), contextpos, EColor::White, EColor::None, 10);

	// 메뉴 아이템 렌더링
	for (int i = 0; i < itemCount; ++i)
	{
		// 아이템 색상 확인
		EColor textColor = (i == currentIndex) ? selectedColor : unselectedColor;
		Vector2 itemPos = titlepos;
		itemPos.y += 18 + itemSpace * i;
		Vector2 itemSize;
		itemSize.x = strlen(items[i]->menuText);
		itemSize.y = 1;

		Game::Get().GetTextImageRenderer()->RenderText(items[i]->menuText, itemPos, textColor, EColor::None, 10);
	}

}
