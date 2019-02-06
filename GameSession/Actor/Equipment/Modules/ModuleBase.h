#pragma once
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CEquipment;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

class CModuleBase
{
public:
	struct ModuleDeleter
	{
		void operator()(CModuleBase* moduleInstance)
		{
			delete moduleInstance;
		}
	};

public:
	CModuleBase(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleBase& dataTemplate);
	virtual ~CModuleBase() = default;

	ModuleID GetID() const;
	ModuleGUID GetGUID() const;

public:
	virtual void Tick();

protected:
	CEquipment& m_ParentEquipment;
	const hvda::CDataTemplateModuleBase& m_Template;

	ModuleID m_ID = MODULE_ID_INVALID;
	ModuleGUID m_GUID = MODULE_GUID_INVALID;
	String m_Name = "";
};

/////////////////////////////////////////////////////////////////////////////

using ModulePtr = std::unique_ptr<CModuleBase, std::function<void(CModuleBase*)>>;

//////////////////////////////////////////////////////////////////////////

} // hvgs
