#pragma once
#include "Actor/Actor.h"
#include "Game/Types.h"

class Tile : public Actor
{

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

