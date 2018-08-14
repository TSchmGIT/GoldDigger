#pragma once

#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"


/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CModuleBase;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CEquipment
{

public:
	CEquipment();
	virtual ~CEquipment() = default;

	void InitAfterCreation();
	void InitAfterLoading();

	void Tick();

protected:
	Map<hvgs::ModuleType, WeakPtr<CModuleBase>> m_ModuleMap;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
