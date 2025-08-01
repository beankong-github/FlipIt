#pragma once
#include "Level/Level.h"


class TestLevel : public Level
{
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;


private:
};

