#pragma once
#include "GameSession/Actor/Economy/EconomyTypes.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Buildings/BuildingInteractiveBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CModuleFuelTank;
class CActorEconomy;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CBuildingFuelStation
	: public CBuildingInteractiveBase
{

public:
	CBuildingFuelStation() = default;
	virtual ~CBuildingFuelStation() = default;

public:
	void Refuel(CModuleFuelTank& fuelTank, CActorEconomy& economy) const;

	static MoneyAmount GetCostPerUnit(FuelType fuelType);

protected:
	virtual ui::SceneID GetUISceneID() const override;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
