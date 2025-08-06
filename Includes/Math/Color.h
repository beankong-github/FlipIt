#pragma once

// »ö»ó.
enum class EColor : int
{
	None = 0,
	Blue = 1,
	Green = 2,
	Red = 4,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	Yellow = 14,
	White = Red | Green | Blue,
	Intensity = 8,
};