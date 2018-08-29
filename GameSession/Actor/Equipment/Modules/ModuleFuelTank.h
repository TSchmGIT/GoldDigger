#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleFuelTank.h"
#include "GameSession/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleFuelTank : public CModuleBase
{

public:
	CModuleFuelTank(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleFuelTank& dataTemplate);
	virtual ~CModuleFuelTank() = default;

	void Tick() override;

public:
	FuelAmount GetCurrentFuelAmount() const;
	void SetCurrentFuelAmount(FuelAmount fuelAmount);

	void SetFuelPenalty(FuelPenalty fuelPenalty, bool isSet);

public:
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
	std::bitset<int(FuelPenalty::Count)>	m_PenaltyMask;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
