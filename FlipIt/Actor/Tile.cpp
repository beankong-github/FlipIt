#include "Tile.h"
#include "Engine.h"
#include "Game/Game.h"
#include "Game/ResourceMgr.h"
#include "Asset/ImageData.h"

Tile::Tile(const char* image, EColor color, const Vector2& position)
	:Actor(image, color, position)
	,tileState(ETileState::None)
	, tileImageData(nullptr)
{
}

Tile::Tile(ETileState state, const Vector2& index)
	: tileState(state)
	, tileImageData(nullptr)
{
	switch (state)
	{
	case ETileState::Front:
	{
		tileImageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, frontImageName));
	}
		break;
	case ETileState::Back:
	{
		tileImageData = dynamic_cast<ImageData*>(Game::Get().ResourceManager()->GetResource(EResourceType::Image, frontImageName));
	}
		break;
	}

	// 타일 이미지가 없으면 안대..!
	assert(tileImageData != nullptr);

	Vector2 pos(0, 0);
	pos.x = tileImageData->Size().x * index.x;
	pos.y = tileImageData->Size().y * index.y;
	Actor(tileImageData->Buffer(), EColor::White, pos);

}

void Tile::Render()
{
	// 타일 그리기
	Engine::Get().WriteToBuffer(*this);
}
