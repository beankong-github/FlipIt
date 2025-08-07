#pragma once
#include "Level/Level.h"
#include <vector>
#include "Actor/Actor.h"
#include <iostream>

struct MenuItem
{
	//typedef void (*OnSelected)();
	using OnSelected = void(*)();

	MenuItem(const char* text, OnSelected onSelected)
		:onSelectedCallBack(onSelected)
	{
		size_t length = strlen(text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, text);
	}


	~MenuItem()
	{
		SafeDeleteArray(menuText);
	}

	// 메뉴 텍스트
	char* menuText = nullptr;

	// 메뉴 선택 시 실행할 동작
	OnSelected onSelectedCallBack = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	virtual ~MenuLevel();

	virtual void Tick(float deltaTime)override;
	virtual void Render() override;

	void AddMenuItem(const char* text, MenuItem::OnSelected callback);

	void SetTitle(const char* title) { this->title = title; };
	void SetContext(const char* context) { this->context = context; }

protected:
	int currentIndex = 0;

	std::string title = "title";
	std::string context = "context blah blah...";

	// 아이템 선택 색상
	EColor selectedColor = EColor::Green;
	EColor unselectedColor = EColor::White;

	// 아이템 배열
	std::vector<MenuItem*> items;
	Vector2 itemPosition = Vector2::Zero;
	int itemSpace = 3;

	// 메뉴 아이템 수
	int itemCount = 0;

};