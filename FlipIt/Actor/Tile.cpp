#include "Tile.h"
#include "Engine.h"

Tile::Tile(const char* image, EColor color, const Vector2& position)
	:Actor(image, color, position)
	,tileState(ETileState::None)
{
}

void Tile::Render()
{
	// Ÿ�� �׸���
	Engine::Get().WriteToBuffer(*this);
}
