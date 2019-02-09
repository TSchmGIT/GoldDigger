#pragma once

#include <GameSessionNew/World/WorldEnums.h>

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
	virtual ~CWorld() = default;

	static CWorld& GetMutable();
	static const CWorld& Get();

public:
	void Init();

	void Tick();

	void Shutdown();

public:
	const Map<ChunkInterval, CChunk>& GetChunks() const;
	CActor& GetActor() const;

	template<class T>
	Optional<const T&> GetBuilding() const;

public:
	std::tuple<ChunkInterval, ChunkSlicePos> WorldToChunkPos(const WorldPos& worldPos) const;

	WorldPos GetTilePos(const WorldPos& worldPos) const;

public:
	Optional<const CTile&> GetTileAt(const WorldPos& worldPos) const;
	void SetTileAt(const WorldPos& worldPos, TileType tileType, bool allowCreation = false);

protected:
	void ConstructActor();
	void ConstructBulidings();

	CChunk& CreateChunk(ChunkInterval worldX);
	void RemoveChunk(ChunkInterval worldX);

	Optional<CChunk&> GetChunk(ChunkInterval worldX);
	Optional<const CChunk&> GetChunk(ChunkInterval worldX) const;

	inline ChunkInterval FindNextChunkPos(int x) const;

protected:
	Map<ChunkInterval, CChunk> m_ChunkMap;

	//////////////////////////////////////////////////////////////////////////
	// Buildings
	Vector<UniquePtr<CBuildingBase>>	m_Buildings;

	UniquePtr<CActor> m_Actor = nullptr;
};

//////////////////////////////////////////////////////////////////////////

template<class T>
Optional<const T&> hvgs::CWorld::GetBuilding() const
{
	for (const auto& building : m_Buildings)
	{
		const T* result = dynamic_cast<const T*>(building.get());
		if (!result)
		{
			continue;
		}

		return *result;
	}

	return boost::none;
}

/////////////////////////////////////////////////////////////////////////////

} // hvgs

