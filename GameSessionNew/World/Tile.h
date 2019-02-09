#pragma once

#include "GameSessionNew/Physics/CollisionObject.h"
#include "GameSessionNew/World/WorldEnums.h"

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

	void Init(const WorldPos& position, TileType tileType);

public:
	TileType GetTileType() const;

	const WorldPos& GetPosition() const;
	WorldPos GetCenter() const;

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
