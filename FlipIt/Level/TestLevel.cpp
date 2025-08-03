#include "TestLevel.h"
#include <iostream>

#include "Actor/Tile.h"


TestLevel::TestLevel()
{
	const char* testTile = "0000000000000\n0000000000000\n0000000000000\n0000000000000\n0000000000000\n0000000000000";

	AddActor(new Tile(testTile, Color::Blue, Vector2(0.f, 0.f)));
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
