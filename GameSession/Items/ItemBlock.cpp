#include "stdafx.h"
#include "ItemBlock.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CItemBlock::CItemBlock(TileType tileType)
	: CItemBase()
	, m_TileType(tileType)
{

}

//////////////////////////////////////////////////////////////////////////

hvgs::TileType CItemBlock::GetTileType() const
{
	return m_TileType;
}

//////////////////////////////////////////////////////////////////////////

String CItemBlock::GetDisplayName() const
{
	switch (m_TileType)
	{
	case hvgs::TileType::Grass:
		return "Grass";
	case hvgs::TileType::Air:
		return "Air";
	case hvgs::TileType::Dirt:
		return "Dirt";
	case hvgs::TileType::Stone:
		return "Stone";
	case hvgs::TileType::IronOre:
		return "Iron Ore";
	case hvgs::TileType::GoldOre:
		return "Gold Ore";
	default:
		return "Block invalid";
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CItemBlock::GetTextureName() const
{
	switch (m_TileType)
	{
	case hvgs::TileType::Dirt:
		return TextureName::ITEM_DIRT;
	case hvgs::TileType::Stone:
		return TextureName::ITEM_STONE;
	case hvgs::TileType::IronOre:
		return TextureName::ITEM_IRON;
	default:
		return TextureName::INVALID;
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
