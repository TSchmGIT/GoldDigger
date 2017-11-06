#include "stdafx.h"
#include "Inventory.h"

#include "GameSession/Items/ItemBase.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CInventory::CInventory()
{

}

//////////////////////////////////////////////////////////////////////////

CInventory::CInventory(const CInventory&)
{

}

//////////////////////////////////////////////////////////////////////////

CInventory::~CInventory()
{

}

//////////////////////////////////////////////////////////////////////////

bool CInventory::HasItems() const
{
	return m_Items.size() > 0;
}

//////////////////////////////////////////////////////////////////////////

void CInventory::AddItem(UniquePtr<CItemBase> itemBase)
{
	m_Items.emplace_back(std::move(itemBase));
}

//////////////////////////////////////////////////////////////////////////

void CInventory::RemoveItemAt(size_t index)
{
	ASSERT_OR_EXECUTE(index >= 0 && index < m_Items.size(), return);

	m_Items.erase(m_Items.begin() + index);
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CItemBase* CInventory::GetItemAt(size_t index) const
{
	ASSERT_OR_EXECUTE(index >= 0, return nullptr);

	if (m_Items.size() == 0)
	{
		return nullptr;
	}

	ASSERT_OR_EXECUTE(index < m_Items.size(), return nullptr);

	return m_Items[index].get();
}

//////////////////////////////////////////////////////////////////////////

const Vector<UniquePtr<hvgs::CItemBase>>& CInventory::GetItems() const
{
	return m_Items;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
