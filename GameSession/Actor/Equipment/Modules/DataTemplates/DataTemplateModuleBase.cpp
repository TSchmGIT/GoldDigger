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
	m_Price = hvgs::MoneyAmount(json["price"].get<hvgs::MoneyAmount::value_type>());
	if (auto textureIt = json.find("texture"); textureIt != json.end())
	{
		m_Texture = hvgs::TextureName(textureIt->get<int>());
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::String& CDataTemplateModuleBase::GetName() const
{
	return m_Name;
}

//////////////////////////////////////////////////////////////////////////

ModuleGUID CDataTemplateModuleBase::GetGUID() const
{
	return m_ModuleGUID;
}

//////////////////////////////////////////////////////////////////////////

hvgs::MoneyAmount CDataTemplateModuleBase::GetPrice() const
{
	return m_Price;
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CDataTemplateModuleBase::GetTexture() const
{
	return m_Texture;
}

//////////////////////////////////////////////////////////////////////////

} // hvda
