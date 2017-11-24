#pragma once
#include "GameSession/Rendering/IRenderElement.h"

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
	CInventory();
	CInventory(const CInventory& other);
	virtual ~CInventory();

public:
	virtual void Draw() const override; // Render element

public:
	bool HasItems() const;

	void AddItem(UniquePtr<CItemBase> itemBase);

	void RemoveItemAt(size_t index);


	const CItemBase* GetItemAt(size_t index) const;
	const Vector<UniquePtr<CItemBase>>& GetItems() const;

protected:
	Vector<UniquePtr<CItemBase>> m_Items;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
