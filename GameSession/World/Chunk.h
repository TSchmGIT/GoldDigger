#pragma once
#include "GameSession/World/ChunkSlice.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CChunkSlice;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CChunk
{

public:
	CChunk(ChunkInterval positionX);
	virtual ~CChunk();

public:
	void UpdateSlicesAt(int yLevel, int yRange);

public:
	const Map<ChunkSliceInterval, CChunkSlice>& GetChunkSlices() const;
	const CChunkSlice* GetChunkSliceAt(int yLevel) const;

public:
	int GetPosX() const;

public:
	const CTile* GetTileAt(int yLevel, const ChunkSlicePos& chunkPos) const;
	void SetTileAt(int yLevel, const ChunkSlicePos& chunkPos, TileType tileType, bool allowCreation = false);

protected:
	inline ChunkSliceInterval FindNextChunkSlicePos(int yLevel) const; ///< Returns the next valid chunk slice y-pos to the given input

	Map<ChunkSliceInterval, CChunkSlice> m_ChunkSliceList;

	ChunkInterval m_PositionX;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
