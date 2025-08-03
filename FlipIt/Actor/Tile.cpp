#include "Tile.h"

Tile::Tile(const char* image, Color color, const Vector2& position)
	:Actor(image, color, position)
	,tileState(ETileState::None)
{
}
