#include "stdafx.h"
#include "DataTemplateModuleBase.h"

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

//////////////////////////////////////////////////////////////////////////

CDataTemplateModuleBase::CDataTemplateModuleBase(const JSON& json)
{
	m_ModuleGUID = ModuleGUID(json["guid"].get<int>());
	m_Name = json["name"].get<hvgs::String>();
	m_Price = hvgs::ModulePrice(json["price"].get<hvgs::ModulePrice::value_type>());
}

//////////////////////////////////////////////////////////////////////////

hvgs::String CDataTemplateModuleBase::GetName() const
{
	return m_Name;
}

//////////////////////////////////////////////////////////////////////////

ModuleGUID CDataTemplateModuleBase::GetGUID() const
{
	return m_ModuleGUID;
}

//////////////////////////////////////////////////////////////////////////

} // hvda
