#pragma once
#include "GameSessionNew/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSessionNew/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSessionNew/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSessionNew/Data/DataDefines.h"

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
	hvgs::FuelAmount GetCapacity() const;
	
protected:
	hvgs::FuelType m_FuelType = hvgs::FuelType::Invalid;
	hvgs::FuelAmount m_Capacity = hvgs::FuelAmount(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvda
