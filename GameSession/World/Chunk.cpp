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
	return m_ChunkSliceMap;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CChunkSlice* CChunk::GetChunkSliceAt(int yLevel) const
{
	auto it = m_ChunkSliceMap.find(FindNextChunkSlicePos(yLevel));

	if (it == m_ChunkSliceMap.end())
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

	auto it = m_ChunkSliceMap.find(yChunkInterval);
	if (it == m_ChunkSliceMap.end())
	{
		return nullptr;
	}

	return &it->second.GetTileAt(chunkPos.x, chunkPos.y);
}

//////////////////////////////////////////////////////////////////////////

void CChunk::SetTileAt(int yLevel, const ChunkSlicePos& chunkPos, TileType tileType, bool allowCreation /*= false*/)
{
	ChunkSliceInterval yChunkInterval = FindNextChunkSlicePos(yLevel);

	auto it = m_ChunkSliceMap.find(yChunkInterval);
	if (it == m_ChunkSliceMap.end())
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

	std::ostringstream ss;
	ss << "Chunk Update " << m_PositionX;
	TT_BEGIN(ss.str());
	for (ChunkSliceInterval i = sliceLevelMin; i < sliceLevelMax; i += CHUNKSLICE_SIZE_Y)
	{
		int height = i;

		auto it = m_ChunkSliceMap.find(height);
		if (it != m_ChunkSliceMap.end())
		{
			continue;
		}

		CChunkSlice slice(this, height);
		slice.CalculateTiles();

		m_ChunkSliceMap.emplace(height, std::move(slice));
	}
	TT_END(ss.str());
}

//////////////////////////////////////////////////////////////////////////

inline ChunkSliceInterval CChunk::FindNextChunkSlicePos(int yLevel) const
{
	if (yLevel >= 0)
	{
		return (yLevel / CHUNKSLICE_SIZE_Y) * CHUNKSLICE_SIZE_Y;
	}
	else
	{
		return ((yLevel + 1 - CHUNKSLICE_SIZE_Y) / CHUNKSLICE_SIZE_Y) * CHUNKSLICE_SIZE_Y;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
