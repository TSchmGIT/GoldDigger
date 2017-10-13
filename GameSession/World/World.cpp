#include "stdafx.h"
#include "World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CWorld* CWorld::s_instance = nullptr;

CWorld::CWorld()
	: m_ChunkPool(32, 100)
{
	s_instance = this;

	TT_BEGIN("Chunk creation");
	for (int i = 0; i < 1; i++)
	{
		int posX = i * CHUNKSLICE_SIZE_X;
		auto chunk = std::make_unique<CChunk>(posX);
		chunk->UpdateSlicesAt(0, CHUNKSLICE_SIZE_Y * 4);

		m_ChunkMap.emplace(posX, std::move(chunk));
	}
	TT_END("Chunk creation");
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

} // hvgs