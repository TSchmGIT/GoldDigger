#include "stdafx.h"
#include "ModuleCargo.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CModuleCargo::CModuleCargo(ModuleID moduleID, CEquipment& equipment, hvda::CDataTemplateModuleCargo dataTemplate, Optional<const CModuleCargo&>)
	: CModuleBase(moduleID, equipment, dataTemplate)
{

}

//////////////////////////////////////////////////////////////////////////

} // hvgs