#include "stdafx.h"
#include "Chunk.h"

#include "GameSession/World/ChunkSlice.h"
#include "GameSession/World/Tile.h"
#include "GameSession/World/WorldEnums.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CChunk::CChunk(ChunkInterval positionX)
	: m_PositionX(positionX)
{
	//LOG_INFO("CHUNK CREATED");
}

//////////////////////////////////////////////////////////////////////////

CChunk::~CChunk()
{
	//LOG_INFO("CHUNK DESTROYED");
}

//////////////////////////////////////////////////////////////////////////

const Map<hvgs::ChunkSliceInterval, hvgs::CChunkSlice>& CChunk::GetChunkSlices() const
{
	return m_ChunkSliceMap;
}

//////////////////////////////////////////////////////////////////////////

hvgs::Optional<const CChunkSlice&> CChunk::GetChunkSliceAt(int yLevel) const
{
	auto it = m_ChunkSliceMap.find(FindNextChunkSlicePos(yLevel));
	if (it == m_ChunkSliceMap.end())
	{
		return boost::none;
	}

	return it->second;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ChunkInterval CChunk::GetPosX() const
{
	return m_PositionX;
}

//////////////////////////////////////////////////////////////////////////

hvgs::Optional<const CTile&> CChunk::GetTileAt(int yLevel, const ChunkSlicePos& chunkPos) const
{
	ChunkSliceInterval yChunkInterval = FindNextChunkSlicePos(yLevel);

	auto it = m_ChunkSliceMap.find(yChunkInterval);
	if (it == m_ChunkSliceMap.end())
	{
		return boost::none;
	}

	return it->second.GetTileAt(chunkPos.x, chunkPos.y);
}

//////////////////////////////////////////////////////////////////////////

void CChunk::SetTileAt(int yLevel, const ChunkSlicePos& chunkPos, TileType tileType, bool allowCreation /*= false*/)
{
	ChunkSliceInterval yChunkInterval = FindNextChunkSlicePos(yLevel);

	CChunkSlice* chunkSlice = nullptr;
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
			CChunkSlice slice{ *this, yChunkInterval };
			auto emplaceResult = m_ChunkSliceMap.emplace(yChunkInterval, std::move(slice));
			chunkSlice = &emplaceResult.first->second;
		}
	}
	else
	{
		chunkSlice = &it->second;
	}

	ASSERT_OR_EXECUTE(chunkSlice, return);
	chunkSlice->SetTileAt(chunkPos.x, chunkPos.y, tileType);
}

//////////////////////////////////////////////////////////////////////////

void CChunk::UpdateSlicesAt(int yLevel, int yRange)
{
	ChunkSliceInterval sliceLevelMax = FindNextChunkSlicePos(yLevel + yRange);
	ChunkSliceInterval sliceLevelMin = FindNextChunkSlicePos(yLevel - yRange);

	//std::ostringstream ss;
	//ss << "Chunk Update " << m_PositionX;
	//TT_BEGIN(ss.str());
	for (ChunkSliceInterval i = sliceLevelMin; i < sliceLevelMax; i += ChunkSliceInterval(CHUNKSLICE_SIZE_Y))
	{
		ChunkSliceInterval height = i;

		auto it = m_ChunkSliceMap.find(height);
		if (it != m_ChunkSliceMap.end())
		{
			continue;
		}

		CChunkSlice slice{ *this, height };
		slice.CalculateTiles();

		m_ChunkSliceMap.emplace(height, std::move(slice));
	}
	//TT_END(ss.str());
}

//////////////////////////////////////////////////////////////////////////

constexpr hvgs::ChunkSliceInterval CChunk::FindNextChunkSlicePos(int yLevel) const
{
	if (yLevel >= 0)
	{
		return ChunkSliceInterval((yLevel / CHUNKSLICE_SIZE_Y) * CHUNKSLICE_SIZE_Y);
	}
	else
	{
		return ChunkSliceInterval(((yLevel + 1 - CHUNKSLICE_SIZE_Y) / CHUNKSLICE_SIZE_Y) * CHUNKSLICE_SIZE_Y);
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
