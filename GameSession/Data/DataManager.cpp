#include "stdafx.h"
#include "DataManager.h"

using json = nlohmann::json;

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

void CDataManager::Init()
{
	LoadModuleList<CDataTemplateModuleHull>("modules_hull.json", m_ModuleHullMap);
	LoadModuleList<CDataTemplateModuleFuelTank>("modules_fueltank.json", m_ModuleFuelTankMap);
	LoadModuleList<CDataTemplateModuleDrill>("modules_drill.json", m_ModuleDrillMap);
	LoadModuleList<CDataTemplateModuleMotor>("modules_motor.json", m_ModuleMotorMap);
	LoadModuleList<CDataTemplateModuleCargo>("modules_cargo.json", m_ModuleCargoMap);
}

//////////////////////////////////////////////////////////////////////////

} // hvda
