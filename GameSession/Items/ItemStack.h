#pragma once
#include "GameSession/World/WorldEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CItemBase;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CItemStack
{

public:
	CItemStack(TileType tileType);
	CItemStack(CItemStack&& other) = default;
	virtual ~CItemStack() = default;

public:
	/// Adds a new item to the stack
	void AddItem(UniquePtr<CItemBase> item);
	/// Removes an item from the stack and returns it
	UniquePtr<CItemBase> RemoveItem();
	/// Removes a range of items from the stack and returns them as a vector
	Vector<UniquePtr<CItemBase>> RemoveItems(int amount);

	/// Returns the maximum allowed capacity of the item stack
	int GetCapacity() const;
	/// Sets the maximum allowed capacity of the item stack
	void SetCapacity(size_t capacity);

	///< Returns the first item of the item stack
	const CItemBase* GetFirstItem() const;

	/// Returns the amount of items that are currently in the item stack
	int GetCurrentAmount() const;
	/// Returns the tile type of the items in the item stack
	TileType GetTileType() const;

public: ///< Convenient helper methods
	bool Empty() const;
	bool Full() const;

protected:
	size_t		m_Capacity = 16; ///< The maximum allowed amount of items in this stack
	TileType	m_TileType = TileType::Invalid;	///< The tile type that is stored in this stack

	Vector<UniquePtr<CItemBase>> m_ItemList; ///< Vector that holds the items owned by this stack
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
