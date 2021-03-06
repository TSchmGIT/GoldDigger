#pragma once

#include "GameSession/Physics/CollisionObject.h"
#include "GameSession/World/WorldEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
enum class Layer : int;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CTile
	: protected ICollisionObject
{

public:
	CTile();
	CTile(const WorldPos& position, TileType tileType);
	virtual ~CTile();

public:
	TileType GetTileType() const;

	const WorldPos& GetPosition() const;

public:
	virtual bool IsEnabled() const override;

protected:
	virtual WorldPos GetAABBOrigin() const override;
	virtual WorldPos GetAABBHalfs() const override;
	virtual Layer GetLayer() const override;

protected:
	TileType m_TileType = TileType::Air;
	WorldPos m_Position = WorldPos();
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
