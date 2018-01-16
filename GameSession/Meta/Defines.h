#pragma once
namespace hvgs
{

using Vector2 = hvmath::Vector2<float>;
using Vector2i = hvmath::Vector2<int>;
using Vector2u = hvmath::Vector2<hvuint>;

using ScreenPos = hvgs::Vector2;

using ChunkInterval = hvsdk::CNamedType<int, struct CHUNK_INTERVAL>; ///< x-position in world space where a chunk begins
using ChunkSliceInterval = hvsdk::CNamedType<int, struct CHUNK_SLICE_INTERVAL>; ///< y-position in world space where a chunk slice begins
using WorldPos = hvgs::Vector2;
using ChunkSlicePos = hvmath::Vector2<hvuint8>; ///< Chunk coords range from x = [0, CHUNK_SIZE_X], y = [0, CHUNK_SIZE_Y]
}