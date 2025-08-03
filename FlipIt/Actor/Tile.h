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

	RTTI_DECLARATIONS(Tile, Actor)

public:	
	Tile(
	const char* image = "",
	EColor color = EColor::White,
	const Vector2& position = Vector2::Zero
	);

	virtual void Render() override;

private:
	ETileState tileState;

};

