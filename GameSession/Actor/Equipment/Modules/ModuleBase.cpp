#include "stdafx.h"
#include "ModuleBase.h"

#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSession/Items/Inventory.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CModuleBase::CModuleBase(ModuleID moduleID, CEquipment& equipment, const hvda::CDataTemplateModuleBase& dataTemplate)
	: m_ParentEquipment(equipment)
	, m_Template(dataTemplate)
	, m_ID(moduleID)
	, m_GUID(dataTemplate.GetGUID())
	, m_Name(dataTemplate.GetName())
{

}

//////////////////////////////////////////////////////////////////////////

ModuleID CModuleBase::GetID() const
{
	return m_ID;
}

//////////////////////////////////////////////////////////////////////////

void CModuleBase::Tick()
{

}

//////////////////////////////////////////////////////////////////////////

} // hvgs
