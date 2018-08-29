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
	for (auto equipmentType = ModuleType(0); equipmentType < ModuleType::Count; equipmentType = ModuleType(int(equipmentType) + 1))
	{
		ModulePtr module = CEquipmentFactory::GetMutable().CreateDefaultModule(equipmentType, *this);

		m_ModuleMap.emplace(equipmentType, std::move(module));
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

} // hvgs
