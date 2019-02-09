#pragma once
#include "GameSessionNew/World/WorldEnums.h"
#include "GameSessionNew/World/Tile.h"

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
	CChunkSlice(const CChunk& parent, ChunkSliceInterval height);
	virtual ~CChunkSlice() = default;

public:
	const CTile& GetTileAt(hvuint8 x, hvuint8 y) const;
	void SetTileAt(hvuint8 x, hvuint8 y, TileType tileType);

	WorldPos GetWorldPos() const;

public:
	void CalculateTiles();

protected:
	inline size_t GetIndex(hvuint8 x, hvuint8 y) const;

protected:
	std::array<CTile, CHUNKSLICE_SIZE_X * CHUNKSLICE_SIZE_Y>	m_Tiles;
	const CChunk&												m_Parent;
	ChunkSliceInterval											m_YLevel = ChunkSliceInterval(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
