#include "stdafx.h"
#include "ItemStack.h"
#include "GameSessionNew/Items/ItemBase.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CItemStack::CItemStack(TileType tileType)
	: m_TileType(tileType)
{
	m_ItemList.reserve(m_Capacity);
}

//////////////////////////////////////////////////////////////////////////

CItemStack::CItemStack(const CItemStack& other)
	: m_Capacity(other.m_Capacity)
	, m_TileType(other.m_TileType)
{
	m_ItemList.clear();
	for (const UniquePtr<CItemBase>& item : other.m_ItemList)
	{
		m_ItemList.emplace_back(std::make_unique<CItemBase>(*item));
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::CItemStack& CItemStack::operator=(const CItemStack& other)
{
	m_Capacity = other.m_Capacity;
	m_TileType = other.m_TileType;

	m_ItemList.clear();
	for (const UniquePtr<CItemBase>& item : other.m_ItemList)
	{
		m_ItemList.emplace_back(std::make_unique<CItemBase>(*item));
	}

	return *this;
}

//////////////////////////////////////////////////////////////////////////

void CItemStack::AddItem(UniquePtr<CItemBase> item)
{
	ASSERT_OR_EXECUTE(item, return);

	if (m_ItemList.size() >= m_Capacity)
	{
		return;
	}

	m_ItemList.emplace_back(std::move(item));
}

//////////////////////////////////////////////////////////////////////////

hvgs::UniquePtr<hvgs::CItemBase> CItemStack::RemoveItem()
{
	if (m_ItemList.empty())
	{
		return nullptr;
	}

	auto back = std::move(m_ItemList.back()); ///< move to result
	m_ItemList.pop_back(); ///< erase invalid and old unique ptr

	return std::move(back); ///< return unique ptr
}

//////////////////////////////////////////////////////////////////////////

hvgs::Vector<hvgs::UniquePtr<hvgs::CItemBase>> CItemStack::RemoveItems(int amount)
{
	amount = hvmath::Min({ amount, int(m_ItemList.size()) });

	Vector<UniquePtr<CItemBase>> result;
	result.reserve(amount);

	for (int i = 0; i < amount; i++)
	{
		auto uniquePtr = std::move(m_ItemList.back());
		m_ItemList.pop_back();
		result.push_back(std::move(uniquePtr));
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////

int CItemStack::GetCapacity() const
{
	return m_Capacity;
}

//////////////////////////////////////////////////////////////////////////

void CItemStack::SetCapacity(size_t capacity)
{
	m_Capacity = capacity;

	// Adjust current stack
	m_ItemList.reserve(m_Capacity);
	if (m_ItemList.size() > capacity)
	{
		m_ItemList.resize(capacity);
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CItemBase* CItemStack::GetFirstItem() const
{
	if (m_ItemList.empty())
	{
		return nullptr;
	}

	return m_ItemList[0].get();
}

//////////////////////////////////////////////////////////////////////////

int CItemStack::GetCurrentAmount() const
{
	return m_ItemList.size();
}

//////////////////////////////////////////////////////////////////////////

hvgs::TileType CItemStack::GetTileType() const
{
	return m_TileType;
}

//////////////////////////////////////////////////////////////////////////

bool CItemStack::Empty() const
{
	return GetCurrentAmount() == 0;
}

//////////////////////////////////////////////////////////////////////////

bool CItemStack::IsFull() const
{
	return m_Capacity > 0 && GetCurrentAmount() == int(m_Capacity);
}

} // hvgs
