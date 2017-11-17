#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CChunkSlice;
class CTile;

enum class TileType : hvuint8;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CChunk
{
public:
	CChunk(ChunkInterval positionX);
	virtual ~CChunk();

public:
	void UpdateSlicesAt(int yLevel, int yRange);

public:
	const Map<ChunkSliceInterval, UniquePtr<CChunkSlice>>& GetChunkSlices() const;
	const CChunkSlice* GetChunkSliceAt(int yLevel) const;

public:
	int GetPosX() const;

public:
	const CTile* GetTileAt(int yLevel, const ChunkSlicePos& chunkPos) const;
	void SetTileAt(int yLevel, const ChunkSlicePos& chunkPos, TileType tileType, bool allowCreation = false);

protected:
	inline ChunkSliceInterval FindNextChunkSlicePos(int yLevel) const; ///< Returns the next valid chunk slice y-pos to the given input

private:
	Map<ChunkSliceInterval, UniquePtr<CChunkSlice>> m_ChunkSliceMap;

	ChunkInterval m_PositionX;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
