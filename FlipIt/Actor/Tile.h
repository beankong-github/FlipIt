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

	Tile(ETileState state, const Vector2& index);

	virtual void Render() override;

private:
	ETileState tileState;
	class ImageData* tileImageData;

	// TODO 하드 코딩 개선 
	const char* frontImageName = "TileFront.txt";
	const char* backImageName= "TileBack.txt";
	const char* blockImageName= "TileFront.txt";
};

