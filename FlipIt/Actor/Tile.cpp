#include "Tile.h"
#include "Engine.h"

Tile::Tile(const char* image, EColor color, const Vector2& position)
	:Actor(image, color, position)
	,tileState(ETileState::None)
{
}

void Tile::Render()
{
	// 타일 그리기
	Engine::Get().WriteToBuffer(*this);
}
