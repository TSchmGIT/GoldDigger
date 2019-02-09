#pragma once
#include "GameSessionNew/Actor/Economy/EconomyTypes.h"
#include "GameSessionNew/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSessionNew/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSessionNew/Data/DataDefines.h"
#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"

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
	const hvgs::String&			GetName() const;
	ModuleGUID					GetGUID() const;
	virtual hvgs::ModuleType	GetType() const = 0;
	hvgs::MoneyAmount			GetPrice() const;

	hvgs::TextureName	GetTexture() const;

protected:
	ModuleGUID m_ModuleGUID = MODULE_GUID_INVALID;
	hvgs::String m_Name = "";
	hvgs::MoneyAmount m_Price = hvgs::MoneyAmount(0);

	hvgs::TextureName m_Texture = hvgs::TextureName::MODULE_TANK_1;
};

/////////////////////////////////////////////////////////////////////////////

} // hvda
