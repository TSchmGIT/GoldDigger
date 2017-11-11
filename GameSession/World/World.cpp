#include "stdafx.h"
#include "World.h"

#include "GameSession/World/Tile.h"
#include "GameSession/World/ChunkSlice.h"
#include "Chunk.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CWorld* CWorld::s_instance = nullptr;

CWorld::CWorld()
	: m_ChunkPool(32, 100)
	//, m_WorkerThread(&CWorld::WorkerThread, this)
{
	s_instance = this;

	m_ChunkMap.reserve(64);


	//TT_BEGIN("Chunk Calculation");
	for (int i = -2; i < 2; i++)
	{
		ChunkInterval posX = i * CHUNKSLICE_SIZE_X;

		UniquePtr<CChunk> chunk = std::make_unique<CChunk>(posX);
		chunk->UpdateSlicesAt(int(-CHUNKSLICE_SIZE_Y * 0.5f), CHUNKSLICE_SIZE_Y * 1);

		m_ChunkMap.emplace(posX, std::move(chunk));
	}
	//TT_END("Chunk Calculation");

}

//////////////////////////////////////////////////////////////////////////

CWorld::~CWorld()
{

}

//////////////////////////////////////////////////////////////////////////

CWorld* CWorld::GetWorld()
{
	return s_instance;
}

//////////////////////////////////////////////////////////////////////////

const Map<int, UniquePtr<CChunk>>& CWorld::GetChunks() const
{
	return m_ChunkMap;
}

//////////////////////////////////////////////////////////////////////////

void CWorld::WorldToChunkPos(const WorldPos& worldPos, ChunkInterval& outWorldX, ChunkSlicePos& outChunkPos) const
{
	outWorldX = FindNextChunkPos(hvmath::Floor<float, int>(worldPos.x));

	if (worldPos.x >= 0.0f)
	{
		outChunkPos.x = hvuint8(hvmath::Mod(worldPos.x, float(CHUNKSLICE_SIZE_X)));
	}
	else
	{
		outChunkPos.x = hvuint8(float(CHUNKSLICE_SIZE_X) + hvmath::Mod(worldPos.x, float(CHUNKSLICE_SIZE_X)));
	}

	if (worldPos.y >= 0.0f)
	{
		outChunkPos.y = hvuint8(hvmath::Mod(worldPos.y, float(CHUNKSLICE_SIZE_Y)));
	}
	else
	{
		outChunkPos.y = hvuint8(float(CHUNKSLICE_SIZE_Y) + hvmath::Mod(worldPos.y, float(CHUNKSLICE_SIZE_Y)));
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CTile* CWorld::GetTileAt(const WorldPos& worldPos) const
{
	ChunkInterval worldX;
	ChunkSlicePos chunkPos;
	WorldToChunkPos(worldPos, worldX, chunkPos);

	// Find Chunk
	auto it = m_ChunkMap.find(worldX);
	if (it == m_ChunkMap.end())
	{
		return nullptr;
	}

	// Find Tile
	return it->second->GetTileAt(hvmath::Floor<float, int>(worldPos.y), chunkPos);
}

//////////////////////////////////////////////////////////////////////////

void CWorld::SetTileAt(const WorldPos& worldPos, TileType tileType, bool allowCreation /*= false*/)
{
	ChunkInterval worldX;
	ChunkSlicePos chunkPos;
	WorldToChunkPos(worldPos, worldX, chunkPos);

	// Find or create Chunk
	auto it = m_ChunkMap.find(worldX);
	CChunk* chunk = nullptr;
	if (it == m_ChunkMap.end())
	{
		if (!allowCreation)
		{
			return;
		}
		else
		{
			chunk = CreateChunk(worldX);
		}
	}
	else
	{
		chunk = it->second.get();
	}

	chunk->SetTileAt(hvmath::Floor<float, int>(worldPos.y), chunkPos, tileType, allowCreation);
}

//////////////////////////////////////////////////////////////////////////

CChunk* CWorld::CreateChunk(ChunkInterval worldX)
{
	auto chunk = std::make_unique<CChunk>(worldX);
	chunk->UpdateSlicesAt(0, CHUNKSLICE_SIZE_Y * 4);

	auto&& pair = m_ChunkMap.emplace(worldX, std::move(chunk));
	return pair.first->second.get();
}

//////////////////////////////////////////////////////////////////////////

inline ChunkInterval CWorld::FindNextChunkPos(int x) const
{
	if (x >= 0)
	{
		return (x / CHUNKSLICE_SIZE_X) * CHUNKSLICE_SIZE_X;
	}
	else
	{
		return ((x + 1 - CHUNKSLICE_SIZE_X) / CHUNKSLICE_SIZE_X) * CHUNKSLICE_SIZE_X;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
