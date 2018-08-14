#pragma once
#include "GameSession/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSession/Data/DataDefines.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataTemplateModuleBase
{
public:
	virtual ~CDataTemplateModuleBase() = default;

protected:
	CDataTemplateModuleBase(const JSON& json);

public:
	hvgs::String GetName() const;
	ModuleGUID GetGUID() const;

protected:
	ModuleGUID m_ModuleGUID = MODULE_GUID_INVALID;
	hvgs::String m_Name = "";
	hvgs::ModulePrice m_Price = hvgs::ModulePrice(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvda
