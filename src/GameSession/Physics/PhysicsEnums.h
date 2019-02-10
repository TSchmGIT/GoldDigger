#pragma once

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

enum class Layer : int
{
	Actor = 1 << 0,
	Environment = 1 << 1,
	Building = 1 << 2
};

enum class CollisionFlags : hvuint8
{
	None = 0U,
	Bottom = 1U,
	Right = 2U,
	Top = 4U,
	Left = 8U
};

//////////////////////////////////////////////////////////////////////////

} // hvgs