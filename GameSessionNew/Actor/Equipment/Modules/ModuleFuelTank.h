#pragma once
#include "GameSessionNew/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleFuelTank.h"
#include "GameSessionNew/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSessionNew/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSessionNew/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleFuelTank : public CModuleBase
{

public:
	CModuleFuelTank(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleFuelTank& dataTemplate, Optional<const CModuleFuelTank&> inheritedTank);
	virtual ~CModuleFuelTank() = default;

	void Tick() override;

public:
	FuelAmount GetCurrentFuelAmount() const;
	void SetCurrentFuelAmount(FuelAmount fuelAmount);

	FuelConsumption GetCurrentBaseConsumption() const;
	void SetCurrentBaseConsumption(FuelConsumption consumption);

	FuelType GetFuelType() const;

	FuelAmount GetMaximumFuelAmount() const;

	void SetFuelPenalty(FuelPenalty fuelPenalty, bool isSet);

public:
	FuelAmount Refuel();

	/// Indicates whether the fuel tank is empty
	bool IsEmpty() const;

	/// Returns the percentage of fuel available in the tank in percent [0..1]
	float GetFuelPercentage() const;


protected:
	const hvda::CDataTemplateModuleFuelTank& GetTemplate() const;

	void TickFuelConsumption();

protected:
	float GetPenaltyConsumptionFactor() const;

protected:
	FuelAmount								m_FuelAmount = FuelAmount(0);

protected:
	FuelConsumption							m_CurrentBaseConsumption = FuelConsumption(0);
	
	std::bitset<int(FuelPenalty::Count)>	m_PenaltyMask;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
