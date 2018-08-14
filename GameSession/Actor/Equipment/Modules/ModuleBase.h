#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CModuleBase
{

public:
	CModuleBase(ModuleID moduleID, const hvda::CDataTemplateModuleBase& dataTemplate);
	virtual ~CModuleBase() = default;

public:
	virtual void Tick();

protected:
	const hvda::CDataTemplateModuleBase& m_Template;

	ModuleID m_ID = MODULE_ID_INVALID;
	ModuleGUID m_GUID = MODULE_GUID_INVALID;
	String m_Name = "";
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
