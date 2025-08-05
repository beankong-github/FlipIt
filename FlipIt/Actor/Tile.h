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

	void Flip(ETileState state = ETileState::Front);

	virtual  inline const char* Image() const override;
	inline ETileState TileState() const { return tileState; }

	// 인덱스 반환
	Vector2 Index() const { return index; };

private:
	ETileState tileState;
	class ImageData* curTileImageData;
	Vector2 index;

	// 꼴보기 싫다 진심
	// TODO 하드 코딩 개선 ===================
	class ImageData* frontTileImageData;
	class ImageData* backTileImageData;
	const EColor frontColor = EColor::White;
	const EColor frontBackgroundColor = EColor::None;
	const EColor backColor = EColor::None;
	const EColor backBackgroundColor = EColor::White;
	static constexpr  const char* frontImageName = "Tile1.txt";
	static constexpr const char* backImageName= "TileBack.txt";
	static constexpr const char* blockImageName= "TileFront.txt";
};

