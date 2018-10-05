#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataTemplateModuleCargo : public CDataTemplateModuleBase
{

public:
	CDataTemplateModuleCargo(const JSON& json);
	virtual ~CDataTemplateModuleCargo() = default;

	hvgs::ModuleType GetType() const override;

};

/////////////////////////////////////////////////////////////////////////////

} // hvda
