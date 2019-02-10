#include "stdafx.h"

#include "GameSession/Actor/Equipment/Equipment.h"
#include "GameSession/Actor/Equipment/EquipmentFactory.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleCargo.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleDrill.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleHull.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleMotor.h"
#include "GameSession/Actor/Equipment/Modules/ModuleCargo.h"
#include "GameSession/Actor/Equipment/Modules/ModuleDrill.h"
#include "GameSession/Actor/Equipment/Modules/ModuleFuelTank.h"
#include "GameSession/Actor/Equipment/Modules/ModuleHull.h"
#include "GameSession/Actor/Equipment/Modules/ModuleMotor.h"
#include "GameSession/Data/DataModuleManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

ModulePtr CEquipmentFactory::CreateDefaultModule(ModuleType moduleType, CEquipment& parentInventory)
{
	ModuleGUID moduleGUID = MODULE_GUID_INVALID;

	switch (moduleType)
	{
	case hvgs::ModuleType::Hull:
		moduleGUID = ModuleGUID(100);
		break;
	case hvgs::ModuleType::Motor:
		moduleGUID = ModuleGUID(200);
		break;
	case hvgs::ModuleType::Drill:
		moduleGUID = ModuleGUID(300);
		break;
	case hvgs::ModuleType::Cargo:
		moduleGUID = ModuleGUID(400);
		break;
	case hvgs::ModuleType::FuelTank:
		moduleGUID = ModuleGUID(500);
		break;
	}

	return std::move(CreateModule(moduleType, moduleGUID, parentInventory, boost::none));
}

//////////////////////////////////////////////////////////////////////////

void CEquipmentFactory::DestroyModule(CModuleBase* moduleInstance)
{
	ASSERT_OR_EXECUTE(moduleInstance, return);

	m_ModuleInstanceMap.erase(moduleInstance->GetID());
}

//////////////////////////////////////////////////////////////////////////

ModulePtr CEquipmentFactory::CreateModule(ModuleType moduleType, ModuleGUID moduleGUID, CEquipment& parentEquipment, Optional<const CModuleBase&> inheritedModule)
{
	switch (moduleType)
	{
	case hvgs::ModuleType::Hull:
	{
		Optional<const CModuleHull&> inheritedHull;
		if (inheritedModule)
		{
			const CModuleBase* baseModule = inheritedModule.get_ptr();
			const CModuleHull* moduleHull = dynamic_cast<const CModuleHull*>(baseModule);
			ASSERT_TEXT(moduleHull, "Created a hull module with non-hull module as inherited module");

			inheritedHull = *moduleHull;
		}
		return std::move(CreateModule<CModuleHull, hvda::CDataTemplateModuleHull>(moduleGUID, parentEquipment, inheritedHull));
	}
	case hvgs::ModuleType::Motor:
	{
		Optional<const CModuleMotor&> inheritedMotor;
		if (inheritedModule)
		{
			const CModuleBase* baseModule = inheritedModule.get_ptr();
			const CModuleMotor* moduleHull = dynamic_cast<const CModuleMotor*>(baseModule);
			ASSERT_TEXT(moduleHull, "Created a motor module with non-motor module as inherited module");

			inheritedMotor = *moduleHull;
		}
		return std::move(CreateModule<CModuleMotor, hvda::CDataTemplateModuleMotor>(moduleGUID, parentEquipment, inheritedMotor));
	}
	case hvgs::ModuleType::Drill:
	{
		Optional<const CModuleDrill&> inheritedDrill;
		if (inheritedModule)
		{
			const CModuleBase* baseModule = inheritedModule.get_ptr();
			const CModuleDrill* moduleDrill = dynamic_cast<const CModuleDrill*>(baseModule);
			ASSERT_TEXT(moduleDrill, "Created a drill module with non-drill module as inherited module");

			inheritedDrill = *moduleDrill;
		}
		return std::move(CreateModule<CModuleDrill, hvda::CDataTemplateModuleDrill>(moduleGUID, parentEquipment, inheritedDrill));
	}
	case hvgs::ModuleType::Cargo:
	{
		Optional<const CModuleCargo&> inheritedCargo;
		if (inheritedModule)
		{
			const CModuleBase* baseModule = inheritedModule.get_ptr();
			const CModuleCargo* moduleCargo = dynamic_cast<const CModuleCargo*>(baseModule);
			ASSERT_TEXT(moduleCargo, "Created a cargo module with non-cargo module as inherited module");

			inheritedCargo = *moduleCargo;
		}
		return std::move(CreateModule<CModuleCargo, hvda::CDataTemplateModuleCargo>(moduleGUID, parentEquipment, inheritedCargo));
	}
	case hvgs::ModuleType::FuelTank:
	{
		Optional<const CModuleFuelTank&> inheritedFuelTank;
		if (inheritedModule)
		{
			const CModuleBase* baseModule = inheritedModule.get_ptr();
			const CModuleFuelTank* moduleFuelTank = dynamic_cast<const CModuleFuelTank*>(baseModule);
			ASSERT_TEXT(moduleFuelTank, "Created a fuel tank module with non-fueltank module as inherited module");

			inheritedFuelTank = *moduleFuelTank;
		}
		return std::move(CreateModule<CModuleFuelTank, hvda::CDataTemplateModuleFuelTank>(moduleGUID, parentEquipment, inheritedFuelTank));
	}
	}

	ASSERT_TEXT(false, "Tried to create module with unknown module type");
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
