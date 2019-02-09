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
	const Map<ChunkSliceInterval, CChunkSlice>& GetChunkSlices() const;
	Optional<const CChunkSlice&> GetChunkSliceAt(int yLevel) const;

public:
	ChunkInterval GetPosX() const;

public:
	Optional<const CTile&> GetTileAt(int yLevel, const ChunkSlicePos& chunkPos) const;
	void SetTileAt(int yLevel, const ChunkSlicePos& chunkPos, TileType tileType, bool allowCreation = false);

protected:
	constexpr ChunkSliceInterval FindNextChunkSlicePos(int yLevel) const; ///< Returns the next valid chunk slice y-pos to the given input

private:
	Map<ChunkSliceInterval, CChunkSlice> m_ChunkSliceMap;

	ChunkInterval m_PositionX;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
