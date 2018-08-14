#include "stdafx.h"
#include "Equipment.h"

#include "GameSession/Actor/Equipment/EquipmentFactory.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/ModuleFuelTank.h"
#include "GameSession/Actor/Equipment/Modules/ModuleHull.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CEquipment::CEquipment()
{
}

//////////////////////////////////////////////////////////////////////////

void CEquipment::InitAfterCreation()
{
	// Fill with default data
	for (auto equipmentType = ModuleType(0); equipmentType < ModuleType::Count; equipmentType = ModuleType(int(equipmentType) + 1))
	{
		WeakPtr<CModuleBase> module = CEquipmentFactory::GetMutable().CreateDefaultModule(equipmentType);

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
		auto& weakPtr = kvPair.second;
		ASSERT_OR_EXECUTE(!weakPtr.expired(), continue);

		auto sharedPtr = weakPtr.lock();
		ASSERT_OR_EXECUTE(sharedPtr, continue);

		sharedPtr->Tick();
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
