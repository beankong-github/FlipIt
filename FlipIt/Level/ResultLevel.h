#pragma once
#include "Level/MenuLevel.h"

class ResultLevel : public MenuLevel
{
	RTTI_DECLARATIONS(ResultLevel, MenuLevel)

public:
	ResultLevel();

	void SetScore(int front, int back);

	virtual void Render() override;

private:
	int frontScore = 0;
	int BackScore = 0;
};