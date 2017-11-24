#include "stdafx.h"
#include "Inventory.h"

#include "GameSession/Items/ItemBase.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"

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

void CInventory::Draw() const
{
	CRenderManager::GetMutable().DrawText(ScreenPos(float(CRenderManager::Get().GetScreenWidth()) - 400.0f, 100.0f), "Inventory", FontName::Arial);

	int counter = 0;
	for (const auto& item : m_Items)
	{
		float y = 200 + counter * 50.0f;

		CRenderManager::GetMutable().DrawText(ScreenPos(float(CRenderManager::Get().GetScreenWidth()) - 400.0f, y), item->GetDisplayName(), FontName::Arial, 40U);
		counter++;
	}
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
