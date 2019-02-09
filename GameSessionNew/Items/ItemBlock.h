#pragma once
#include "GameSessionNew/Items/Itembase.h"
#include "World/WorldEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CItemBlock : public CItemBase
{

public:
	CItemBlock() = default;
	CItemBlock(TileType tileType);
	virtual ~CItemBlock() = default;

	TileType GetTileType() const;

	virtual String GetDisplayName() const override;
	virtual TextureName GetTextureName() const override;

protected:
	TileType m_TileType = TileType::Air;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
