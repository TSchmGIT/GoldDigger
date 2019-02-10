#include "stdafx.h"
#include "ActorEconomy.h"
#include "Data/DataModuleManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

hvgs::MoneyAmount CActorEconomy::GetMoney() const
{
	return m_Money;
}

//////////////////////////////////////////////////////////////////////////

void CActorEconomy::SetMoney(MoneyAmount amount)
{
	m_Money = amount;
}

//////////////////////////////////////////////////////////////////////////

void CActorEconomy::AddMoney(MoneyAmount amount)
{
	m_Money += amount;
}

//////////////////////////////////////////////////////////////////////////

hvgs::MoneyAmount CActorEconomy::RemoveMoney(MoneyAmount amount)
{
	MoneyAmount reducedAmount = amount;
	if (reducedAmount >= m_Money)
	{
		LOG_ERROR("TRIED TO REMOVE MORE MONEY THAN AVAILABLE");
		reducedAmount = m_Money;
	}

	m_Money -= reducedAmount;

	return reducedAmount;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CActorEconomy::ModuleOwnershipArray& CActorEconomy::GetOwnedModuleList() const
{
	return m_OwnedModuleList;
}

//////////////////////////////////////////////////////////////////////////

void CActorEconomy::AddOwnedModule(ModuleGUID moduleGUID, ModuleType moduleType /*= ModuleType::Invalid*/)
{
	if (moduleType == ModuleType::Invalid)
	{
		moduleType = hvda::CDataModuleManager::Get().GetModuleType(moduleGUID);
	}

	ASSERT_OR_EXECUTE(moduleType != hvgs::ModuleType::Invalid, return);

	auto& ownedModuleList = m_OwnedModuleList[size_t(moduleType)];
	ASSERT_OR_EXECUTE_TEXT(ownedModuleList.find(moduleGUID) == ownedModuleList.end(), "Tried to add an already owned moduleGUID to the owned list", return);
	ownedModuleList.emplace(moduleGUID);
}

//////////////////////////////////////////////////////////////////////////

bool CActorEconomy::HasOwnership(ModuleGUID moduleGUID, ModuleType moduleType /*= ModuleType::Invalid*/) const
{
	if (moduleType == ModuleType::Invalid)
	{
		moduleType = hvda::CDataModuleManager::Get().GetModuleType(moduleGUID);
	}

	ASSERT_OR_EXECUTE(moduleType != hvgs::ModuleType::Invalid, return false);
	auto& ownedModuleList = m_OwnedModuleList[size_t(moduleType)];

	return ownedModuleList.find(moduleGUID) != ownedModuleList.end();
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
