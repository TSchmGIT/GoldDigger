#pragma once
#include "GameSession/Items/Itembase.h"
#include "World/WorldEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CItemBlock : public CItemBase
{

public:
	CItemBlock();
	CItemBlock(TileType tileType);

	virtual ~CItemBlock();

	TileType GetTileType() const;

protected:
	TileType m_TileType = TileType::Air;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
