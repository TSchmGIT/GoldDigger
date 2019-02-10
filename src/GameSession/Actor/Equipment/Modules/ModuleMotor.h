#pragma once
#include "DataTemplates/DataTemplateModuleMotor.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleMotor : public CModuleBase
{

public:
	CModuleMotor(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleMotor& dataTemplate, Optional<const CModuleMotor&> inheritedMotor);
	virtual ~CModuleMotor() = default;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs