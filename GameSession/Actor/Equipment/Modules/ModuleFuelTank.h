#pragma once
#include "GameSession/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleFuelTank.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleFuelTank : public CModuleBase
{

public:
	CModuleFuelTank(ModuleID moduleID, const hvda::CDataTemplateModuleFuelTank& dataTemplate);
	virtual ~CModuleFuelTank() = default;

	void Tick() override;

public:
	FuelAmount GetCurrentFuelAmount() const;
	void SetCurrentFuelAmount(FuelAmount fuelAmount);

protected:
	FuelAmount m_FuelAmount = FuelAmount(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
