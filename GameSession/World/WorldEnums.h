#pragma once

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

const hvuint8 CHUNKSLICE_SIZE_X = 16;
const hvuint8 CHUNKSLICE_SIZE_Y = 16;

enum class TileType : hvuint8
{
	Invalid = 0,
	Grass,
	Air,
	Dirt,
	Stone,
	IronOre,
	GoldOre,
	Count
};

//////////////////////////////////////////////////////////////////////////

} // hvgs
