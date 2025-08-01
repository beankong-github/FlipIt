#include "TestLevel.h"
#include <iostream>

TestLevel::TestLevel()
{
}

void TestLevel::BeginPlay()
{
	Super::BeginPlay();

	printf("Test Level Opend! \n");
}

void TestLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void TestLevel::Render()
{
	Super::Render();

}
