#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Data/DataDefines.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataTemplateModuleFuelTank : public CDataTemplateModuleBase
{

public:
	CDataTemplateModuleFuelTank(const JSON& json);
	virtual ~CDataTemplateModuleFuelTank() = default;

	hvgs::ModuleType GetType() const override;

public:
	hvgs::FuelType GetFuelType() const;
	hvgs::FuelConsumption GetConsumption() const;
	hvgs::FuelAmount GetCapacity() const;
	
protected:
	hvgs::FuelType m_FuelType = hvgs::FuelType::Invalid;
	hvgs::FuelConsumption m_Consumption = hvgs::FuelConsumption(0);
	hvgs::FuelAmount m_Capacity = hvgs::FuelAmount(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvda
