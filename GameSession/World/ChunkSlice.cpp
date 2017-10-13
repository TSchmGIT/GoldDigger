#include "stdafx.h"
#include "ChunkSlice.h"

#include "GameSession/World/Chunk.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CChunkSlice::CChunkSlice(const CChunk* parent, int height)
	: m_Parent(parent)
	, m_YLevel(height)
{

}

//////////////////////////////////////////////////////////////////////////

CChunkSlice::~CChunkSlice()
{

}

//////////////////////////////////////////////////////////////////////////

hvgs::TileType CChunkSlice::GetTileAt(hvuint8 x, hvuint8 y) const
{
	return m_Tiles[GetIndex(x, y)];
}

//////////////////////////////////////////////////////////////////////////

Vector2i CChunkSlice::GetWorldPos() const
{
	ASSERT_OR_EXECUTE(m_Parent, return Vector2i());
	return Vector2i(m_Parent->GetPosX(), m_YLevel);
}

//////////////////////////////////////////////////////////////////////////

void CChunkSlice::CalculateTiles()
{
	FastNoiseSIMD* noise = FastNoiseSIMD::NewFastNoiseSIMD();
	float* noiseMap = noise->GetSimplexSet(m_Parent->GetPosX(), m_YLevel, 0, CHUNKSLICE_SIZE_X, CHUNKSLICE_SIZE_Y, 1);

	for (hvuint8 x = 0; x < CHUNKSLICE_SIZE_X; x++)
		for (hvuint8 y = 0; y < CHUNKSLICE_SIZE_Y; y++)
		{
			size_t index = GetIndex(x, y);
			float noiseValue = noiseMap[index];

			TileType tileType;
			if (noiseValue < 0.5f)
			{
				tileType = TileType::Dirt;
			}
			else
			{
				tileType = TileType::Stone;
			}

			m_Tiles[index] = tileType;
		}
}

//////////////////////////////////////////////////////////////////////////

inline size_t CChunkSlice::GetIndex(hvuint8 x, hvuint8 y) const
{
	return y + x * CHUNKSLICE_SIZE_Y;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
