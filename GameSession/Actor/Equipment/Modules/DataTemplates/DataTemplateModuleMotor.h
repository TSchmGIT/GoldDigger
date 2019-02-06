#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataTemplateModuleMotor : public CDataTemplateModuleBase
{

public:
	CDataTemplateModuleMotor(const JSON& json);
	virtual ~CDataTemplateModuleMotor() = default;

	hvgs::ModuleType GetType() const override;

protected:
	hvgs::FuelConsumption m_Consumption = hvgs::FuelConsumption(0);

};

/////////////////////////////////////////////////////////////////////////////

} // hvda
