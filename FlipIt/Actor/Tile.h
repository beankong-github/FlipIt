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
	EColor backgroundColor = EColor::None,
	const Vector2& position = Vector2::Zero,
	const Vector2 & size = Vector2::Zero
	);

	Tile(ETileState state, const Vector2& index);

	virtual void Render() override;

	virtual  inline const char* Image() const override;

	inline ETileState TileState() const { return tileState; }

private:
	ETileState tileState;
	class ImageData* tileImageData;

	// TODO 하드 코딩 개선 
	static constexpr  const char* frontImageName = "TileFront.txt";
	static constexpr const char* backImageName= "TileBack.txt";
	static constexpr const char* blockImageName= "TileFront.txt";
};

