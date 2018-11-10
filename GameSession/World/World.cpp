#include "stdafx.h"
#include "World.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Buildings/BuildingBase.h"
#include "GameSession/Buildings/BuildingBroker.h"
#include "GameSession/Manager/GameManager.h"
#include "GameSession/World/Chunk.h"
#include "GameSession/World/ChunkSlice.h"
#include "GameSession/World/Tile.h"
#include "Buildings/BuildingWorkshop.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CWorld::CWorld()
{
	constexpr int amountChunks = 8;
	m_ChunkMap.reserve(amountChunks * amountChunks * 2);

	TT_BEGIN("Chunk Calculation");
	for (int i = -amountChunks; i < amountChunks; i++)
	{
		ChunkInterval posX(i * CHUNKSLICE_SIZE_X);

		CreateChunk(posX);
	}
	TT_END("Chunk Calculation");
}

//////////////////////////////////////////////////////////////////////////

CWorld& CWorld::GetMutable()
{
	return CGameManager::Get().GetWorld();
}

//////////////////////////////////////////////////////////////////////////

const CWorld& CWorld::Get()
{
	return CGameManager::Get().GetWorld();
}

//////////////////////////////////////////////////////////////////////////

void CWorld::Init()
{
	ConstructActor();
	ConstructBulidings();
}

//////////////////////////////////////////////////////////////////////////

void CWorld::Tick()
{
	if (!m_Actor)
	{
		return;
	}

	const WorldPos& actorPos = m_Actor->GetPosition();
	auto[actorInterval, actorChunkSlice] = WorldToChunkPos(actorPos);

	ChunkInterval lowerBound = actorInterval - ChunkInterval(CHUNKSLICE_SIZE_X * 4);
	ChunkInterval upperBound = actorInterval + ChunkInterval(CHUNKSLICE_SIZE_X * 4);

	for (ChunkInterval i = lowerBound; i < upperBound; i += ChunkInterval(CHUNKSLICE_SIZE_X))
	{
		if (GetChunk(i))
		{
			continue;
		}

		CreateChunk(i);
	}

	for (auto it = m_ChunkMap.begin(); it != m_ChunkMap.end(); /* no increment */)
	{
		ChunkInterval chunkInterval = it->first;
		bool inBounds = chunkInterval >= lowerBound && chunkInterval <= upperBound;
		if (inBounds)
		{
			++it;
			continue;
		}
		else
		{
			it = m_ChunkMap.erase(it);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CWorld::Shutdown()
{
	m_ChunkMap.clear();
	m_Buildings.clear();
	m_Actor.reset();
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Map<ChunkInterval, CChunk>& CWorld::GetChunks() const
{
	return m_ChunkMap;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CActor& CWorld::GetActor() const
{
	return *m_Actor;
}

//////////////////////////////////////////////////////////////////////////

std::tuple<hvgs::ChunkInterval, hvgs::ChunkSlicePos> CWorld::WorldToChunkPos(const WorldPos& worldPos) const
{
	ChunkInterval outWorldX = FindNextChunkPos(hvmath::Floor<int>(worldPos.x));


	ChunkSlicePos outChunkPos;
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

	return { outWorldX, outChunkPos };
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CWorld::GetTilePos(const WorldPos& worldPos) const
{
	return WorldPos(hvmath::Floor<float, float>(worldPos.x), hvmath::Floor<float, float>(worldPos.y));
}

//////////////////////////////////////////////////////////////////////////

hvgs::Optional<const CTile&> CWorld::GetTileAt(const WorldPos& worldPos) const
{
	auto[worldX, chunkPos] = WorldToChunkPos(worldPos);

	// Find Chunk
	auto it = m_ChunkMap.find(worldX);
	if (it == m_ChunkMap.end())
	{
		return boost::none;
	}

	// Find Tile
	return it->second.GetTileAt(hvmath::Floor<int>(worldPos.y), chunkPos);
}

//////////////////////////////////////////////////////////////////////////

void CWorld::SetTileAt(const WorldPos& worldPos, TileType tileType, bool allowCreation /*= false*/)
{
	auto[worldX, chunkPos] = WorldToChunkPos(worldPos);

	// Find or create Chunk
	Optional<CChunk&> chunk = GetChunk(worldX);
	if (!chunk)
	{
		if (!allowCreation)
		{
			return;
		}

		chunk = CreateChunk(worldX);
	}

	chunk->SetTileAt(hvmath::Floor<int>(worldPos.y), chunkPos, tileType, allowCreation);
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
	m_Buildings.reserve(2);
	auto& buildingBroker = m_Buildings.emplace_back(std::make_unique<CBuildingBroker>());
	buildingBroker->SetPosition({ 3.0f, 0.0f });

	auto& buildingWorkshop = m_Buildings.emplace_back(std::make_unique<CBuildingWorkshop>());
	buildingWorkshop->SetPosition({ 6.0, 0.0f });
}

//////////////////////////////////////////////////////////////////////////

hvgs::CChunk& CWorld::CreateChunk(ChunkInterval worldX)
{
	// Create chunk
	auto emplaceResult = m_ChunkMap.emplace(worldX, worldX); //< key = worldX, value = implicit ctor of CChunk
	auto& chunk = emplaceResult.first->second;

	// Update terrain
	chunk.UpdateSlicesAt(-32, 40);

	return chunk;
}

//////////////////////////////////////////////////////////////////////////

void CWorld::RemoveChunk(ChunkInterval worldX)
{
	auto itFind = m_ChunkMap.find(worldX);
	if (itFind == m_ChunkMap.end())
	{
		ASSERT_TEXT(false, "Tried to remove a chunk at a position where no chunk is existing");
		return;
	}

	m_ChunkMap.erase(worldX);
}

//////////////////////////////////////////////////////////////////////////

hvgs::Optional<CChunk&> CWorld::GetChunk(ChunkInterval worldX)
{
	// Try to find chunk interval in map
	auto it = m_ChunkMap.find(worldX);
	if (it == m_ChunkMap.end())
	{
		return boost::none;
	}

	return it->second;
}

//////////////////////////////////////////////////////////////////////////

hvgs::Optional<const CChunk&> CWorld::GetChunk(ChunkInterval worldX) const
{
	// Try to find chunk interval in map
	auto it = m_ChunkMap.find(worldX);
	if (it == m_ChunkMap.end())
	{
		return boost::none;
	}

	return it->second;
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
