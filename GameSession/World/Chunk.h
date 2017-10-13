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
	CChunk(int positionX);
	virtual ~CChunk();

public:
	void UpdateSlicesAt(int yLevel, int yRange);

public:
	const Map<int, CChunkSlice>& GetChunkSlices() const;

public:
	int GetPosX() const;

protected:

	inline int GetSliceYLevel(int yLevel) const;

	Map<int, CChunkSlice> m_ChunkSliceList;

	int m_PositionX;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
