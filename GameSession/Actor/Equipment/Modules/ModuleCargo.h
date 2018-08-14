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
	CModuleCargo(ModuleID moduleID, hvda::CDataTemplateModuleCargo dataTemplate);
	virtual ~CModuleCargo() = default;

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
