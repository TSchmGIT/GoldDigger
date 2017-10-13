#pragma once
#include "GameSession/World/Chunk.h"

/////////////////////////////////////////////////////////////////////////////

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

protected:
	Map<int, UniquePtr<CChunk>> m_ChunkMap;

	hvsdk::CObjectPool<CChunk>	m_ChunkPool;

private:
	static CWorld* s_instance;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs

