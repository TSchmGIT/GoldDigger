#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleDrill.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleDrill : public CModuleBase
{

public:
	CModuleDrill(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleDrill& dataTemplate);
	virtual ~CModuleDrill() = default;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
