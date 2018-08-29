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
#include "GameSession/Data/DataManager.h"

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

	return std::move(CreateModule(moduleType, moduleGUID, parentInventory));
}

//////////////////////////////////////////////////////////////////////////

void CEquipmentFactory::DestroyModule(CModuleBase* moduleInstance)
{
	ASSERT_OR_EXECUTE(moduleInstance, return);

	m_ModuleInstanceMap.erase(moduleInstance->GetID());
}

//////////////////////////////////////////////////////////////////////////

ModulePtr CEquipmentFactory::CreateModule(ModuleType moduleType, ModuleGUID moduleGUID, CEquipment& parentEquipment)
{
	switch (moduleType)
	{
		case hvgs::ModuleType::Hull:
		{
			return std::move(CreateModule<CModuleHull, hvda::CDataTemplateModuleHull>(moduleGUID, parentEquipment));
		}
		case hvgs::ModuleType::Motor:
		{
			return std::move(CreateModule<CModuleMotor, hvda::CDataTemplateModuleMotor>(moduleGUID, parentEquipment));
		}
		case hvgs::ModuleType::Drill:
		{
			return std::move(CreateModule<CModuleDrill, hvda::CDataTemplateModuleDrill>(moduleGUID, parentEquipment));
		}
		case hvgs::ModuleType::Cargo:
		{
			return std::move(CreateModule<CModuleCargo, hvda::CDataTemplateModuleCargo>(moduleGUID, parentEquipment));
		}
		case hvgs::ModuleType::FuelTank:
		{
			return std::move(CreateModule<CModuleFuelTank, hvda::CDataTemplateModuleFuelTank>(moduleGUID, parentEquipment));
		}
	}

	ASSERT_TEXT(false, "Tried to create module with unknown module type");
	//auto foo = [](ModuleID) {};
	return ModulePtr(nullptr, nullptr);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
