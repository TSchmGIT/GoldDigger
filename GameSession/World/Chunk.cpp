#include "stdafx.h"
#include "Chunk.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CChunk::CChunk(ChunkInterval positionX)
	: m_PositionX(positionX)
{
}

//////////////////////////////////////////////////////////////////////////

CChunk::~CChunk()
{

}

//////////////////////////////////////////////////////////////////////////

const Map<ChunkSliceInterval, hvgs::CChunkSlice>& CChunk::GetChunkSlices() const
{
	return m_ChunkSliceList;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CChunkSlice* CChunk::GetChunkSliceAt(int yLevel) const
{
	auto it = m_ChunkSliceList.find(FindNextChunkSlicePos(yLevel));

	if (it == m_ChunkSliceList.end())
	{
		return nullptr;
	}
	else
	{
		return &it->second;
	}
}

//////////////////////////////////////////////////////////////////////////

int CChunk::GetPosX() const
{
	return m_PositionX;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CTile* CChunk::GetTileAt(int yLevel, const ChunkSlicePos& chunkPos) const
{
	ChunkSliceInterval yChunkInterval = FindNextChunkSlicePos(yLevel);

	auto it = m_ChunkSliceList.find(yChunkInterval);
	if (it == m_ChunkSliceList.end())
	{
		return nullptr;
	}

	return &it->second.GetTileAt(chunkPos.x, chunkPos.y);
}

//////////////////////////////////////////////////////////////////////////

void CChunk::SetTileAt(int yLevel, const ChunkSlicePos& chunkPos, TileType tileType, bool allowCreation /*= false*/)
{
	ChunkSliceInterval yChunkInterval = FindNextChunkSlicePos(yLevel);

	auto it = m_ChunkSliceList.find(yChunkInterval);
	if (it == m_ChunkSliceList.end())
	{
		if (!allowCreation)
		{
			return;
		}
		else
		{
			// Create chunk slice
			return;
		}
	}

	it->second.SetTileAt(chunkPos.x, chunkPos.y, tileType);
}

//////////////////////////////////////////////////////////////////////////

void CChunk::UpdateSlicesAt(int yLevel, int yRange)
{
	ChunkSliceInterval sliceLevelMax = FindNextChunkSlicePos(yLevel + yRange);
	ChunkSliceInterval sliceLevelMin = FindNextChunkSlicePos(yLevel - yRange);

	for (ChunkSliceInterval i = sliceLevelMin; i < sliceLevelMax; i += CHUNKSLICE_SIZE_Y)
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

inline ChunkSliceInterval CChunk::FindNextChunkSlicePos(int yLevel) const
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
