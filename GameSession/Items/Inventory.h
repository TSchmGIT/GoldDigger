#pragma once
#include "GameSession/Rendering/IRenderElement.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CItemBase;
class CItemStack;
}

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CInventory
	: public IRenderElement
{

public:
	CInventory();
	CInventory(const CInventory& other);
	virtual ~CInventory();

public:
	virtual void Draw() const override; // Render element

public:
	bool HasItems() const;

	void AddItem(UniquePtr<CItemBase> itemBase);

	void RemoveAllItems();
	void RemoveStackAt(size_t index);

	CItemStack* GetStackAt(size_t index);
	const Vector<UniquePtr<CItemStack>>& GetStackList() const;

protected:
	Vector<UniquePtr<CItemStack>> m_ItemStackList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
