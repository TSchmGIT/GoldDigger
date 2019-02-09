#pragma once
#include "GameSessionNew/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleCargo.h"
#include "GameSessionNew/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleCargo : public CModuleBase
{

public:
	CModuleCargo(ModuleID moduleID, CEquipment& equipment, hvda::CDataTemplateModuleCargo dataTemplate, Optional<const CModuleCargo&> inheritedCargo);
	virtual ~CModuleCargo() = default;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
