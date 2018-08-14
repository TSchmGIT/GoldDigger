#include "stdafx.h"

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

hvgs::WeakPtr<hvgs::CModuleBase> CEquipmentFactory::CreateDefaultModule(ModuleType moduleType)
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

	return CreateModule(moduleType, moduleGUID);
}

//////////////////////////////////////////////////////////////////////////

hvgs::WeakPtr<hvgs::CModuleBase> CEquipmentFactory::CreateModule(ModuleType moduleType, ModuleGUID guid)
{
	switch (moduleType)
	{
	case hvgs::ModuleType::Hull:
	{
		return CreateModule<CModuleHull, hvda::CDataTemplateModuleHull>(guid);
	}
	case hvgs::ModuleType::Motor:
	{
		return CreateModule<CModuleMotor, hvda::CDataTemplateModuleMotor>(guid);
	}
	case hvgs::ModuleType::Drill:
	{
		return CreateModule<CModuleDrill, hvda::CDataTemplateModuleDrill>(guid);
	}
	case hvgs::ModuleType::Cargo:
	{
		return CreateModule<CModuleCargo, hvda::CDataTemplateModuleCargo>(guid);
	}
	case hvgs::ModuleType::FuelTank:
	{
		return CreateModule<CModuleFuelTank, hvda::CDataTemplateModuleFuelTank>(guid);
	}
	}

	ASSERT_TEXT(false, "Tried to create module with unknown module type");
	return hvgs::WeakPtr<hvgs::CModuleBase>();
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
