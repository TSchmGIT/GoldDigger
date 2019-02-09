#pragma once
#include "GameSessionNew/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSessionNew/Actor/Equipment/Modules/DefinesModules.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataTemplateModuleHull : public CDataTemplateModuleBase
{

public:
	CDataTemplateModuleHull(const JSON& json);
	virtual ~CDataTemplateModuleHull() = default;

	hvgs::ModuleType GetType() const override;

public:
	hvgs::HullPoints GetMaxHP() const;

protected:
	hvgs::HullPoints m_MaxHP = hvgs::HullPoints(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvda
