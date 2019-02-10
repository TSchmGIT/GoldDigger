#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataTemplateModuleDrill : public CDataTemplateModuleBase
{

public:
	CDataTemplateModuleDrill(const JSON& json);
	virtual ~CDataTemplateModuleDrill() = default;

	hvgs::ModuleType GetType() const override;
};

/////////////////////////////////////////////////////////////////////////////

} // hvda