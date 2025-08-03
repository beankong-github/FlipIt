#include "TestLevel.h"
#include <iostream>

#include "Actor/Tile.h"


// TODO
// 1. 파일로 타일 읽어와서 출력

TestLevel::TestLevel()
{
	const char* testTile = "0000000000000\n0000000000000\n0000000000000\n0000000000000\n0000000000000\n0000000000000";

	AddActor(new Tile(testTile, EColor::Blue, Vector2(0, 0)));
}

void TestLevel::BeginPlay()
{
	Super::BeginPlay();
	

}

void TestLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void TestLevel::Render()
{
	Super::Render();

}
