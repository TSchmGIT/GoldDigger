#include "stdafx.h"
#include "Chunk.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CChunk::CChunk(int positionX)
	: m_PositionX(positionX)
{
}

//////////////////////////////////////////////////////////////////////////

CChunk::~CChunk()
{

}

//////////////////////////////////////////////////////////////////////////

const Map<int, hvgs::CChunkSlice>& CChunk::GetChunkSlices() const
{
	return m_ChunkSliceList;
}

//////////////////////////////////////////////////////////////////////////

int CChunk::GetPosX() const
{
	return m_PositionX;
}

//////////////////////////////////////////////////////////////////////////

void CChunk::UpdateSlicesAt(int yLevel, int yRange)
{
	int sliceLevelMax = GetSliceYLevel(yLevel + yRange);
	int sliceLevelMin = GetSliceYLevel(yLevel - yRange);

	for (int i = sliceLevelMin; i < sliceLevelMax; i += CHUNKSLICE_SIZE_Y)
	{
		int height = i;

		auto it = m_ChunkSliceList.find(height);
		if (it != m_ChunkSliceList.end())
		{
			continue;
		}

		CChunkSlice slice(this, height);
		slice.CalculateTiles();

		m_ChunkSliceList.emplace(height, std::move(slice));
	}
}

//////////////////////////////////////////////////////////////////////////

int CChunk::GetSliceYLevel(int yLevel) const
{
	if (yLevel > 0)
	{
		return (yLevel / CHUNKSLICE_SIZE_Y) * CHUNKSLICE_SIZE_Y;
	}
	else
	{
		return ((yLevel - CHUNKSLICE_SIZE_Y) / CHUNKSLICE_SIZE_Y) * CHUNKSLICE_SIZE_Y;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
