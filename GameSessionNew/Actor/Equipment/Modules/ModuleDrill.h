#pragma once
#include "GameSessionNew/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleDrill.h"
#include "GameSessionNew/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleDrill : public CModuleBase
{

public:
	CModuleDrill(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleDrill& dataTemplate, Optional<const CModuleDrill&> inheritedDrill);
	virtual ~CModuleDrill() = default;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
