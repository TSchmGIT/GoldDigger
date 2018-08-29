#include "stdafx.h"
#include "ModuleMotor.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CModuleMotor::CModuleMotor(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleMotor& dataTemplate)
	: CModuleBase(moduleID, equipment, dataTemplate)
{

}

//////////////////////////////////////////////////////////////////////////

} // hvgs
