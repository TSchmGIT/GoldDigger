#include "stdafx.h"
#include "Equipment.h"

#include "GameSessionNew/Actor/Actor.h"
#include "GameSessionNew/Actor/Economy/ActorEconomy.h"
#include "GameSessionNew/Actor/Equipment/EquipmentFactory.h"
#include "GameSessionNew/Actor/Equipment/Modules/ModuleFuelTank.h"
#include "GameSessionNew/Actor/Equipment/Modules/ModuleHull.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CEquipment::CEquipment(CActor& parentActor)
	: m_Actor(parentActor)
{

}

//////////////////////////////////////////////////////////////////////////

void CEquipment::InitAfterCreation()
{
	// Fill with default data
	for (auto moduleType = ModuleType(0); moduleType < ModuleType::Count; moduleType = ModuleType(int(moduleType) + 1))
	{
		ModulePtr moduleInstance = CEquipmentFactory::GetMutable().CreateDefaultModule(moduleType, *this);
		ModuleGUID moduleGuid = moduleInstance->GetGUID();

		m_ModuleMap.emplace(moduleType, std::move(moduleInstance));

		// Register ownership for default modules	
		auto& economy = m_Actor.GetEconomy();
		economy.AddOwnedModule(moduleGuid, moduleType);
	}
}

//////////////////////////////////////////////////////////////////////////

void CEquipment::InitAfterLoading()
{
	// Fill with loaded data
}

//////////////////////////////////////////////////////////////////////////

void CEquipment::Tick()
{
	// Tick all modules
	for (const auto& kvPair : m_ModuleMap)
	{
		auto& moduleInstance = kvPair.second;
		moduleInstance->Tick();
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::CModuleBase* CEquipment::GetModule(hvgs::ModuleType moduleType) const
{
	auto itFind = m_ModuleMap.find(moduleType);
	if (itFind != m_ModuleMap.end())
	{
		return itFind->second.get();
	}
	else
	{
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////

void CEquipment::ReplaceModule(ModuleType moduleType, ModuleGUID moduleGUID)
{
	Optional<const CModuleBase&> inheritedModule;
	if (auto itFind = m_ModuleMap.find(moduleType);
		itFind != m_ModuleMap.end())
	{
		inheritedModule = *itFind->second.get();
	}
	ModulePtr moduleInstance = CEquipmentFactory::GetMutable().CreateModule(moduleType, moduleGUID, *this, inheritedModule);
	m_ModuleMap[moduleType] = std::move(moduleInstance);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
