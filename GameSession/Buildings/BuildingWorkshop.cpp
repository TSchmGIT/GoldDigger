#include "stdafx.h"
#include "BuildingWorkshop.h"
#include "Actor/Equipment/Equipment.h"
#include "Actor/Economy/ActorEconomy.h"
#include "Data/DataModuleManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshop::PurchaseModule(CActorEconomy& economy, CEquipment& equipment, ModuleType moduleType, ModuleGUID moduleGUID) const
{
	const auto* moduleTemplate = hvda::CDataModuleManager::Get().GetModuleTemplate(moduleGUID, moduleType);
	ASSERT_OR_EXECUTE(moduleTemplate, return);

	// Pay price
	auto moduleCosts = moduleTemplate->GetPrice();
	economy.RemoveMoney(moduleCosts);

	// Replace module in equipment
	equipment.ReplaceModule(moduleType, moduleGUID);
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::SceneID CBuildingWorkshop::GetUISceneID() const
{
	return ui::SceneID::BuildingWorkshop;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
