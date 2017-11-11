#include "stdafx.h"
#include "ChunkSlice.h"

#include "GameSession/World/Chunk.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CChunkSlice::CChunkSlice(const CChunk* parent, ChunkInterval height)
	: m_Parent(parent)
	, m_YLevel(height)
{

}
//
////////////////////////////////////////////////////////////////////////////
//
//CChunkSlice::CChunkSlice(const CChunkSlice& other)
//{
//	m_Parent = other.m_Parent;
//	m_YLevel = other.m_YLevel;
//
//	for (size_t i = 0; i < CHUNKSLICE_SIZE_X * CHUNKSLICE_SIZE_Y; i++)
//	{
//		m_Tiles[i] = other.m_Tiles[i];
//	}
//}
//
////////////////////////////////////////////////////////////////////////////
//
//CChunkSlice::CChunkSlice(CChunkSlice&& other)
//	: m_Parent(std::move(other.m_Parent))
//	, m_YLevel(other.m_YLevel)
//{
//	std::move(m_Tiles, m_Tiles + CHUNKSLICE_SIZE_X * CHUNKSLICE_SIZE_Y, std::back_inserter(other.m_YLevel));
//}
//
////////////////////////////////////////////////////////////////////////////

CChunkSlice::~CChunkSlice()
{

}

//////////////////////////////////////////////////////////////////////////

const CTile& CChunkSlice::GetTileAt(hvuint8 x, hvuint8 y) const
{
	ASSERT_TEXT(x >= 0 && x < CHUNKSLICE_SIZE_X && y >= 0 && y < CHUNKSLICE_SIZE_Y, "GetTileAt() was out of range");
	return m_Tiles[GetIndex(x, y)];
}

//////////////////////////////////////////////////////////////////////////

void CChunkSlice::SetTileAt(hvuint8 x, hvuint8 y, TileType tileType)
{
	ASSERT_OR_EXECUTE(x >= 0 && x < CHUNKSLICE_SIZE_X && y >= 0 && y < CHUNKSLICE_SIZE_Y, return);
	m_Tiles[GetIndex(x, y)] = CTile(GetWorldPos() + WorldPos(float(x), float(y)), tileType);
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CChunkSlice::GetWorldPos() const
{
	ASSERT_OR_EXECUTE(m_Parent, return Vector2i());
	return WorldPos(float(m_Parent->GetPosX()), float(m_YLevel));
}

//////////////////////////////////////////////////////////////////////////

void CChunkSlice::CalculateTiles()
{
	FastNoiseSIMD* noise = FastNoiseSIMD::NewFastNoiseSIMD();
	float* noiseMap = noise->GetSimplexSet(m_Parent->GetPosX(), m_YLevel, 0, CHUNKSLICE_SIZE_X, CHUNKSLICE_SIZE_Y, 1, 10.0f);

	for (hvuint8 x = 0; x < CHUNKSLICE_SIZE_X; x++)
		for (hvuint8 y = 0; y < CHUNKSLICE_SIZE_Y; y++)
		{
			size_t index = GetIndex(x, y);
			float noiseValue = noiseMap[index];

			TileType tileType;
			if (noiseValue >= 0.85f)
			{
				tileType = TileType::IronOre;
			}
			else if (noiseValue >= 0.3f)
			{
				tileType = TileType::Stone;
			}
			else
			{
				tileType = TileType::Dirt;
			}

			m_Tiles[index].Init(GetWorldPos() + WorldPos(float(x), float(y)), tileType);
		}
}

//////////////////////////////////////////////////////////////////////////

inline size_t CChunkSlice::GetIndex(hvuint8 x, hvuint8 y) const
{
	return y + x * CHUNKSLICE_SIZE_Y;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
