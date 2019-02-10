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

}

//////////////////////////////////////////////////////////////////////////

CTile::~CTile()
{

}

//////////////////////////////////////////////////////////////////////////

void CTile::Init(const WorldPos& position, TileType tileType)
{
	m_Position = position;
	m_TileType = tileType;
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

hvgs::WorldPos CTile::GetCenter() const
{
	static const Vector2 offset(0.5f, 0.5f);
	return m_Position + offset;
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
