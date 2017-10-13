#pragma once

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

const hvuint8 CHUNKSLICE_SIZE_X = 16;
const hvuint8 CHUNKSLICE_SIZE_Y = 16;
const float	  TILE_SPRITE_SIZE = 32;

enum class TileType : hvuint8
{
	Grass = 0,
	Dirt,
	Stone,
	IronOre,
	GoldOre,
	Count
};

//////////////////////////////////////////////////////////////////////////

} // hvgs
