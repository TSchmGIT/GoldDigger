#include "stdafx.h"
#include "DataModuleManager.h"

using json = nlohmann::json;

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

void CDataModuleManager::Init()
{
	LoadModuleList<CDataTemplateModuleHull>("modules_hull.json", m_ModuleHullMap);
	LoadModuleList<CDataTemplateModuleFuelTank>("modules_fueltank.json", m_ModuleFuelTankMap);
	LoadModuleList<CDataTemplateModuleDrill>("modules_drill.json", m_ModuleDrillMap);
	LoadModuleList<CDataTemplateModuleMotor>("modules_motor.json", m_ModuleMotorMap);
	LoadModuleList<CDataTemplateModuleCargo>("modules_cargo.json", m_ModuleCargoMap);
}

//////////////////////////////////////////////////////////////////////////

const CDataTemplateModuleBase* CDataModuleManager::GetModuleTemplate(ModuleGUID moduleGUID, hvgs::ModuleType moduleType) const
{
	switch (moduleType)
	{
	case hvgs::ModuleType::Hull:
		return GetModuleTemplate<CDataTemplateModuleHull>(moduleGUID);
	case hvgs::ModuleType::Motor:
		return GetModuleTemplate<CDataTemplateModuleMotor>(moduleGUID);
	case hvgs::ModuleType::Drill:
		return GetModuleTemplate<CDataTemplateModuleDrill>(moduleGUID);
	case hvgs::ModuleType::Cargo:
		return GetModuleTemplate<CDataTemplateModuleCargo>(moduleGUID);
	case hvgs::ModuleType::FuelTank:
		return GetModuleTemplate<CDataTemplateModuleFuelTank>(moduleGUID);
	default:
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Map<ModuleGUID, hvgs::UniquePtr<hvda::CDataTemplateModuleBase>>& CDataModuleManager::GetModuleMap(hvgs::ModuleType moduleType) const
{
	if (moduleType == hvgs::ModuleType::Hull)
	{
		return m_ModuleHullMap;
	}
	else if (moduleType == hvgs::ModuleType::Motor)
	{
		return m_ModuleMotorMap;
	}
	else if (moduleType == hvgs::ModuleType::Drill)
	{
		return m_ModuleDrillMap;
	}
	else if (moduleType == hvgs::ModuleType::Cargo)
	{
		return m_ModuleCargoMap;
	}
	else if (moduleType == hvgs::ModuleType::FuelTank)
	{
		return m_ModuleFuelTankMap;
	}

	return m_ModuleCargoMap;
}

//////////////////////////////////////////////////////////////////////////

} // hvda
