#include "stdafx.h"
#include "Tile.h"

#include "GameSession/Physics/PhysicsEnums.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CTile::CTile()
{

}

//////////////////////////////////////////////////////////////////////////

CTile::CTile(const WorldPos& position, TileType tileType)
	: m_Position(position)
	, m_TileType(tileType)
{
	m_AABB.pos = GetAABBOrigin();
	m_AABB.half = GetAABBHalfs();
}

//////////////////////////////////////////////////////////////////////////

CTile::~CTile()
{

}

//////////////////////////////////////////////////////////////////////////

hvgs::TileType CTile::GetTileType() const
{
	return m_TileType;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::WorldPos& CTile::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

bool CTile::IsEnabled() const
{
	return m_TileType != TileType::Air;
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CTile::GetAABBOrigin() const
{
	return m_Position + WorldPos(0.5f, 0.5f);
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CTile::GetAABBHalfs() const
{
	return{ 0.5f, 0.5f };
}

//////////////////////////////////////////////////////////////////////////

Layer CTile::GetLayer() const
{
	return Layer::Environment;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
