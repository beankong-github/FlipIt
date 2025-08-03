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
	Tile(
	const char* image = "",
	Color color = Color::White,
	const Vector2& position = Vector2::Zero
	);
private:
	ETileState tileState;

};

