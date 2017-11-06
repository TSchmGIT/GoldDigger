#pragma once
#include "GameSession/World/Chunk.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CTile;
class CChunk;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CWorld
{

public:
	CWorld();
	virtual ~CWorld();

	static CWorld* GetWorld();

public:
	const Map<int, UniquePtr<CChunk>>& GetChunks() const;

public:
	void WorldToChunkPos(const WorldPos& worldPos, ChunkInterval& outWorldX, ChunkSlicePos& outChunkPos) const;

public:
	const CTile* GetTileAt(const WorldPos& worldPos) const;
	void SetTileAt(const WorldPos& worldPos, TileType tileType, bool allowCreation = false);

private:
	void WorkerThread();

protected:
	CChunk* CreateChunk(ChunkInterval worldX);

	inline ChunkInterval FindNextChunkPos(int x) const;

protected:
	Map<ChunkInterval, UniquePtr<CChunk>> m_ChunkMap;
	Map<ChunkInterval, UniquePtr<CChunk>> m_ChunkMapBack;

	hvsdk::CObjectPool<CChunk>	m_ChunkPool;

private:
	static CWorld* s_instance;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

