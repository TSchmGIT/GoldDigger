#pragma once
#include "GameSession/World/WorldEnums.h"
#include "GameSession/World/Tile.h"

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
	const CTile& GetTileAt(hvuint8 x, hvuint8 y) const;
	void SetTileAt(hvuint8 x, hvuint8 y, TileType tileType);

	WorldPos GetWorldPos() const;

public:
	void CalculateTiles();

protected:
	inline size_t GetIndex(hvuint8 x, hvuint8 y) const;

	CTile m_Tiles[CHUNKSLICE_SIZE_X * CHUNKSLICE_SIZE_Y];

	const CChunk*	m_Parent;
	int				m_YLevel;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
