#pragma once

#include "GameSession/Buildings/BuildingInteractiveBase.h"
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
	CBuildingWorkshop() = default;
	virtual ~CBuildingWorkshop() = default;

public:
	void PurchaseModule(CActorEconomy& economy, CEquipment& equipment, ModuleType moduleType, ModuleGUID moduleGUID) const;

protected:
	virtual ui::SceneID GetUISceneID() const override;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
