#pragma once

#include <GameSession/World/WorldEnums.h>

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CTile;
class CChunk;
class CActor;
class CBuildingBase;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CWorld
{

public:
	CWorld();
	virtual ~CWorld();

	static CWorld* GetMutable();
	static const CWorld* Get();

public:
	void Init();

public:
	const Map<ChunkInterval, UniquePtr<CChunk>>& GetChunks() const;
	const CActor& GetActor() const;
	CActor& GetActor();

	template<class T>
	const T* GetBuilding() const;

public:
	void WorldToChunkPos(const WorldPos& worldPos, ChunkInterval& outWorldX, ChunkSlicePos& outChunkPos) const;

	WorldPos GetTilePos(const WorldPos& worldPos) const;

public:
	const CTile* GetTileAt(const WorldPos& worldPos) const;
	void SetTileAt(const WorldPos& worldPos, TileType tileType, bool allowCreation = false);

protected:
	void ConstructActor();
	void ConstructBulidings();

	CChunk* CreateChunk(ChunkInterval worldX);

	inline ChunkInterval FindNextChunkPos(int x) const;

protected:
	Map<ChunkInterval, UniquePtr<CChunk>> m_ChunkMap;

	hvsdk::CObjectPool<CChunk>	m_ChunkPool;

	//////////////////////////////////////////////////////////////////////////
	// Buildings
	Vector<UniquePtr<CBuildingBase>>	m_Buildings;

private:
	static CWorld* s_instance;

	UniquePtr<CActor> m_Actor = nullptr;
};

//////////////////////////////////////////////////////////////////////////

template<class T>
const T* hvgs::CWorld::GetBuilding() const
{
	for (const auto& building : m_Buildings)
	{
		const T* result = dynamic_cast<const T*>(building.get());
		if (!result)
		{
			continue;
		}

		return result;
	}

	return nullptr;
}

/////////////////////////////////////////////////////////////////////////////

} // hvgs

