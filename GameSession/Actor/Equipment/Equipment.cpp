#include "stdafx.h"
#include "Equipment.h"

#include "GameSession/Actor/Equipment/EquipmentFactory.h"
#include "GameSession/Actor/Equipment/Modules/ModuleFuelTank.h"
#include "GameSession/Actor/Equipment/Modules/ModuleHull.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

void CEquipment::InitAfterCreation()
{
	// Fill with default data
	for (auto moduleType = ModuleType(0); moduleType < ModuleType::Count; moduleType = ModuleType(int(moduleType) + 1))
	{
		ModulePtr module = CEquipmentFactory::GetMutable().CreateDefaultModule(moduleType, *this);

		m_ModuleMap.emplace(moduleType, std::move(module));
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
	ModulePtr module = CEquipmentFactory::GetMutable().CreateModule(moduleType, moduleGUID, *this);
	m_ModuleMap.emplace(moduleType, std::move(module));
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
