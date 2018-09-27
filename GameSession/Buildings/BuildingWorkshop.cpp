#include "stdafx.h"
#include "BuildingWorkshop.h"
#include "Actor/Equipment/Equipment.h"
#include "Actor/Economy/ActorEconomy.h"
#include "Data/DataModuleManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshop::PurchaseModule(CActorEconomy&, CEquipment& equipment, ModuleType moduleType, ModuleGUID moduleGUID)
{
	ReplaceModule(equipment, moduleType, moduleGUID);

	//hvda::CDataModuleManager::Get().GetModuleTemplate()
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshop::ReplaceModule(CEquipment& equipment, ModuleType moduleType, ModuleGUID moduleGUID)
{
	equipment.ReplaceModule(moduleType, moduleGUID);
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::SceneID CBuildingWorkshop::GetUISceneID() const
{
	return ui::SceneID::BuildingWorkshop;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
