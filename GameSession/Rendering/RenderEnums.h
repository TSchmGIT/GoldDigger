#pragma once

namespace hvgs
{
const hvuint8 BASE_TILE_SIZE_PX = 76;

enum class Alignment
{
	Left = 0,
	TopLeft,
	BottomLeft,

	Center,
	CenterTop,
	CenterBottom,

	Right,	
	TopRight,
	BottomRight,
};
}
