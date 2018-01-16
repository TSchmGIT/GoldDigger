#include "stdafx.h"
#include "Inventory.h"

#include "GameSession/Items/ItemBase.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Fonts/EnumsFont.h"
#include "ItemStack.h"
#include "ItemBlock.h"

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
	CRenderManager::GetMutable().DrawText(ScreenPos(float(CRenderManager::Get().GetScreenWidth()) - 400.0f, 100.0f), "Inventory", Alignment::TopLeft, FontName::Arial);

	int counter = 0;
	for (const auto& itemStack : m_ItemStackList)
	{
		float y = 200 + counter * 50.0f;

		const auto* item = itemStack->GetFirstItem();
		ASSERT_OR_EXECUTE(item, continue);

		String text = item->GetDisplayName() + " (" + std::to_string(itemStack->GetCurrentAmount()) + ")";

		CRenderManager::GetMutable().DrawText(ScreenPos(float(CRenderManager::Get().GetScreenWidth()) - 400.0f, y), text, Alignment::TopLeft, FontName::Arial, 40U);
		counter++;
	}
}

//////////////////////////////////////////////////////////////////////////

bool CInventory::HasItems() const
{
	return m_ItemStackList.size() > 0;
}

//////////////////////////////////////////////////////////////////////////

void CInventory::AddItem(UniquePtr<CItemBase> itemBase)
{
	ASSERT_OR_EXECUTE(itemBase, return);
	const auto* itemBlock = dynamic_cast<const CItemBlock*>(itemBase.get());
	ASSERT_OR_EXECUTE(itemBlock, return);

	for (auto& itemStack : m_ItemStackList)
	{
		if (itemStack->GetTileType() != itemBlock->GetTileType())
		{
			continue;
		}

		if (itemStack->Full())
		{
			continue;
		}

		itemStack->AddItem(std::move(itemBase));
		return;
	}

	// Create new item stack and add item to it
	CItemStack stack(itemBlock->GetTileType());
	stack.AddItem(std::move(itemBase));

	// Add stack to list
	m_ItemStackList.push_back(std::make_unique<CItemStack>(std::move(stack)));
}

//////////////////////////////////////////////////////////////////////////

void CInventory::RemoveAllItems()
{
	m_ItemStackList.clear();
}

//////////////////////////////////////////////////////////////////////////

void CInventory::RemoveStackAt(size_t index)
{
	ASSERT_OR_EXECUTE(index >= 0 && index < m_ItemStackList.size(), return);

	m_ItemStackList.erase(m_ItemStackList.begin() + index);
}

//////////////////////////////////////////////////////////////////////////

hvgs::CItemStack* CInventory::GetStackAt(size_t index)
{
	if (m_ItemStackList.size() == 0)
	{
		return nullptr;
	}

	ASSERT_OR_EXECUTE(index < m_ItemStackList.size(), return nullptr);
	return m_ItemStackList[index].get();
}

//////////////////////////////////////////////////////////////////////////

const Vector<UniquePtr<hvgs::CItemStack>>& CInventory::GetStackList() const
{
	return m_ItemStackList;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
