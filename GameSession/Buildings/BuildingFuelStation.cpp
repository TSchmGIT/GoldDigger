#include "stdafx.h"
#include "BuildingFuelStation.h"
#include "Actor/Economy/ActorEconomy.h"
#include "Actor/Equipment/Modules/ModuleFuelTank.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

void CBuildingFuelStation::Refuel(CModuleFuelTank& fuelTank, CActorEconomy& economy) const
{
	// Refuel tank
	auto refueledAmount = fuelTank.Refuel();

	// Reduce economy
	auto fuelType = fuelTank.GetFuelType();
	auto moneyCostsPerUnit = GetCostPerUnit(fuelType);
	auto totalCosts = MoneyAmount(MoneyAmount::value_type(moneyCostsPerUnit.get() * refueledAmount.get()));
	economy.RemoveMoney(totalCosts);
}

//////////////////////////////////////////////////////////////////////////

hvgs::MoneyAmount CBuildingFuelStation::GetCostPerUnit(FuelType fuelType)
{
	float costsPerMillion;

	switch (fuelType)
	{
	case hvgs::FuelType::Oil:
		costsPerMillion = 100.0f;
		break;
	case hvgs::FuelType::Gas:
		costsPerMillion = 500.0f;
		break;
	default:
		ASSERT_TEXT(false, "Tried to get fuel costs for invalid fuel type");
		return MoneyAmount(0);
	}

	return MoneyAmount(MoneyAmount::value_type(costsPerMillion / 1000000.0f));
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::SceneID CBuildingFuelStation::GetUISceneID() const
{
	return ui::SceneID::BuildingFuelStation;
}

} // hvgs
