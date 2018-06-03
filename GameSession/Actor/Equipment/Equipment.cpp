#include "stdafx.h"
#include "Equipment.h"

#include "GameSession/Actor/Equipment/Modules/BaseModule.h"
#include "GameSession/Actor/Equipment/Modules/ModuleCargo.h"
#include "GameSession/Actor/Equipment/Modules/ModuleDrill.h"
#include "GameSession/Actor/Equipment/Modules/ModuleFuelTank.h"
#include "GameSession/Actor/Equipment/Modules/ModuleHull.h"
#include "GameSession/Actor/Equipment/Modules/ModuleMotor.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CEquipment::CEquipment()
{
	for (GDData::EquipmentType equipmentType = GDData::EquipmentType(0); equipmentType < GDData::EquipmentType::Count; equipmentType = GDData::EquipmentType(int(equipmentType) + 1))
	{
		UniquePtr<CBaseModule> module = nullptr;

		switch (equipmentType)
		{
		case GDData::EquipmentType::Hull:
			module = std::make_unique<CModuleHull>();
			break;
		case GDData::EquipmentType::Motor:
			module = std::make_unique<CModuleMotor>();
			break;
		case GDData::EquipmentType::Drill:
			module = std::make_unique<CModuleDrill>();
			break;
		case GDData::EquipmentType::Cargo:
			module = std::make_unique<CModuleCargo>();
			break;
		case GDData::EquipmentType::FuelTank:
			module = std::make_unique<CModuleFuelTank>();
			break;
		}

		m_ModuleList.emplace(equipmentType, std::move(module));
	}
}

//////////////////////////////////////////////////////////////////////////

void CEquipment::InitAfterCreation()
{
	// Fill with default data
}

//////////////////////////////////////////////////////////////////////////

void CEquipment::InitAfterLoading()
{
	// Fill with loaded data
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
