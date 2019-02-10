#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleHull.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleHull : public CModuleBase
{

public:
	CModuleHull(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleHull& dataTemplate, Optional<const CModuleHull&> inheritedHull);
	virtual ~CModuleHull() = default;

public:
	HullPoints GetHP() const;
	void SetHP(HullPoints hp);

protected:
	HullPoints m_HP = HullPoints(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
