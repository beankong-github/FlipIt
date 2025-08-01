#pragma once
#include "Actor/Actor.h"

class Tile : public Actor
{
	enum ETileState
	{
		None = -1,
		Player1,
		Player2,
		Block,
		MAX
	};

public:

private:
	ETileState tileState;

};

