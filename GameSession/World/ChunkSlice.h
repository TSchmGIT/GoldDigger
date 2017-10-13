#pragma once
#include "GameSession/World/WorldEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CChunk;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CChunkSlice
{

public:
	CChunkSlice(const CChunk* parent, int height);
	virtual ~CChunkSlice();

public:
	TileType GetTileAt(hvuint8 x, hvuint8 y) const;

	Vector2i GetWorldPos() const;

public:
	void CalculateTiles();

protected:
	inline size_t GetIndex(hvuint8 x, hvuint8 y) const;

	TileType m_Tiles[CHUNKSLICE_SIZE_X * CHUNKSLICE_SIZE_Y];

	const CChunk*	m_Parent;
	int				m_YLevel;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
