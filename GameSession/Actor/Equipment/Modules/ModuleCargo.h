#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleCargo.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"

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
