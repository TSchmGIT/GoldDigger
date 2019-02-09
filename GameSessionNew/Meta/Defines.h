#pragma once
namespace hvgs
{

using hvint8 = int8_t;
using hvint16 = int16_t;
using hvint64 = int64_t;

using hvuint8 = uint8_t;
using hvuint16 = uint16_t;
using hvuint = uint32_t;
using hvuint64 = uint64_t;

using Vector2 = hvmath::Vector2<float>;
using Vector2i = hvmath::Vector2<int>;
using Vector2u = hvmath::Vector2<hvuint>;

using ScreenPos = hvgs::Vector2;

using ChunkInterval = hvsdk::CNamedType<int, struct CHUNK_INTERVAL>; ///< x-position in world space where a chunk begins
using ChunkSliceInterval = hvsdk::CNamedType<int, struct CHUNK_SLICE_INTERVAL>; ///< y-position in world space where a chunk slice begins
using WorldPos = hvgs::Vector2;
using ChunkSlicePos = hvmath::Vector2<hvuint8>; ///< Chunk coords range from x = [0, CHUNK_SIZE_X], y = [0, CHUNK_SIZE_Y]
}