#pragma once
#include "GameSessionNew/Items/ItemStack.h"
#include "GameSessionNew/Rendering/IRenderElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CItemBase;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CInventory
	: public IRenderElement
{

public:
	CInventory() = default;
	virtual ~CInventory() = default;

public:
	virtual void Draw() const override; // Render element

public:
	bool HasItems() const;

	void AddItem(UniquePtr<CItemBase> itemBase);

	void RemoveAllItems();
	void RemoveStackAt(size_t index);

	CItemStack* GetStackAt(size_t index);
	const Vector<CItemStack>& GetStackList() const;

protected:
	Vector<CItemStack> m_ItemStackList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
