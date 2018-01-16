#include "stdafx.h"
#include "World.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Buildings/BuildingBase.h"
#include "GameSession/Buildings/BuildingBroker.h"
#include "GameSession/World/Chunk.h"
#include "GameSession/World/ChunkSlice.h"
#include "GameSession/World/Tile.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CWorld* CWorld::s_instance = nullptr;

CWorld::CWorld()
	: m_ChunkPool(32, 100)
{
	s_instance = this;

	m_ChunkMap.reserve(64);

	TT_BEGIN("Chunk Calculation");
	for (int i = -4; i < 4; i++)
	{
		ChunkInterval posX(i * CHUNKSLICE_SIZE_X);

		UniquePtr<CChunk> chunk = std::make_unique<CChunk>(posX);
		chunk->UpdateSlicesAt(-32, 40);

		m_ChunkMap.emplace(posX, std::move(chunk));
	}
	TT_END("Chunk Calculation");

	//ChunkInterval leftMostX(-5 * CHUNKSLICE_SIZE_X);
	//ChunkInterval rightMostX(4 * CHUNKSLICE_SIZE_X);

	//UniquePtr<CChunk> chunkLeftMost = std::make_unique<CChunk>(leftMostX);
	//UniquePtr<CChunk> chunkRightMost = std::make_unique<CChunk>(rightMostX);

	//for (int y = -256; y < 64; ++y)
	//{
	//	chunkLeftMost->SetTileAt(y, ChunkSlicePos(CHUNKSLICE_SIZE_X - 1, ((y % CHUNKSLICE_SIZE_Y) + CHUNKSLICE_SIZE_Y) % CHUNKSLICE_SIZE_Y), TileType::Stone, true);
	//	chunkRightMost->SetTileAt(y, ChunkSlicePos(0, ((y % CHUNKSLICE_SIZE_Y) + CHUNKSLICE_SIZE_Y) % CHUNKSLICE_SIZE_Y), TileType::Stone, true);
	//}

	//m_ChunkMap.emplace(leftMostX, std::move(chunkLeftMost));
	//m_ChunkMap.emplace(rightMostX, std::move(chunkRightMost));
}

//////////////////////////////////////////////////////////////////////////

CWorld::~CWorld()
{

}

//////////////////////////////////////////////////////////////////////////

CWorld* CWorld::GetMutable()
{
	return s_instance;
}

//////////////////////////////////////////////////////////////////////////

const CWorld* CWorld::Get()
{
	return s_instance;
}

//////////////////////////////////////////////////////////////////////////

void CWorld::Construct()
{
	ConstructActor();
	ConstructBulidings();
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Map<ChunkInterval, UniquePtr<hvgs::CChunk>>& CWorld::GetChunks() const
{
	return m_ChunkMap;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CActor& CWorld::GetActor() const
{
	return *m_Actor;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CActor& CWorld::GetActor()
{
	return *m_Actor;
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

hvgs::WorldPos CWorld::GetTilePos(const WorldPos& worldPos) const
{
	return WorldPos(hvmath::Floor<float, float>(worldPos.x), hvmath::Floor<float, float>(worldPos.y));
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

void CWorld::ConstructActor()
{
	m_Actor = std::make_unique<CActor>();
	m_Actor->SetPosition(WorldPos({ 0.0f, 0.0f }));
}

//////////////////////////////////////////////////////////////////////////

void CWorld::ConstructBulidings()
{
	// Broker
	m_Buildings.reserve(1);
	auto& buildingBroker = m_Buildings.emplace_back(std::make_unique<CBuildingBroker>());
	buildingBroker->SetPosition({ 3.0f, 0.0f });
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
		return ChunkInterval((x / CHUNKSLICE_SIZE_X) * CHUNKSLICE_SIZE_X);
	}
	else
	{
		return ChunkInterval(((x + 1 - CHUNKSLICE_SIZE_X) / CHUNKSLICE_SIZE_X) * CHUNKSLICE_SIZE_X);
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
