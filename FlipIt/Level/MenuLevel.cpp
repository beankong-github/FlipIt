#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

MenuLevel::MenuLevel()
{
}

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}
	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	//Super::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + itemCount) % itemCount;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % itemCount;
	}
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelectedCallBack();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

}

void MenuLevel::Render()
{
	Super::Render();

	// �޴� ������ ������
	for (int i = 0; i < itemCount; ++i)
	{
		// ������ ���� Ȯ��
		EColor textColor = (i == currentIndex) ? selectedColor : unselectedColor;
		Vector2 itemPos = itemPosition;
		itemPos.y += itemSpace * i;
		Vector2 itemSize;
		itemSize.x = strlen(items[i]->menuText);
		itemSize.y = 1;

		Engine::Get().WriteToBuffer(itemPos, itemSize, items[i]->menuText, textColor, EColor::None, 10);
	}
}

void MenuLevel::AddMenuItem(const char* text, MenuItem::OnSelected callback)
{
	items.emplace_back(new MenuItem(text, callback));

	itemCount = static_cast<int>(items.size());
}
