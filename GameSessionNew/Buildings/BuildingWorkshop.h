#pragma once

#include "GameSessionNew/Buildings/BuildingInteractiveBase.h"
#include "Actor/Equipment/Modules/EnumsModules.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CActorEconomy;
class CEquipment;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingWorkshop
	: public CBuildingInteractiveBase
{
public:
	CBuildingWorkshop();
	virtual ~CBuildingWorkshop() = default;

public:
	void PurchaseModule(CActorEconomy& economy, CEquipment& equipment, ModuleType moduleType, ModuleGUID moduleGUID) const;

protected:
	ui::SceneID GetUISceneID() const override;
	TextureName GetBuildingTexture() const override;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
