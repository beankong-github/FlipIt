#pragma once

#define REVERSE(state) (ETileState)!(bool)(state)

enum class ETileState
{
	None = -1,
	Front,
	Back,
	Block,
	MAX
};

enum class EResourceType
{
	None = -1,
	Image,
	Map,
	MAX
};

enum class EDirection
{
	None = -1,
	Up,
	Down,
	Left,
	Right,
	MAX
};
