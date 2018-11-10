#pragma once

#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSession/Actor/Equipment/Modules/ModuleBase.h"


/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CModuleHull;
class CModuleMotor;
class CModuleDrill;
class CModuleCargo;
class CModuleFuelTank;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CEquipment
{

public:
	CEquipment() = default;
	virtual ~CEquipment() = default;

	void InitAfterCreation();
	void InitAfterLoading();

	void Tick();

public:
	CModuleBase* GetModule(ModuleType moduleType) const;
	template<class ModuleClass>	ModuleClass* GetModule() const;

	void ReplaceModule(ModuleType moduleType, ModuleGUID moduleGUID);

protected:
	Map<ModuleType, ModulePtr> m_ModuleMap;
};

//////////////////////////////////////////////////////////////////////////

template<class ModuleClass>
ModuleClass* hvgs::CEquipment::GetModule() const
{
	CModuleBase* moduleBase = nullptr;
	if constexpr (std::is_same_v<ModuleClass, CModuleHull>)
	{
		moduleBase = GetModule(ModuleType::Hull);
	}
	else if constexpr (std::is_same_v<ModuleClass, CModuleMotor>)
	{
		moduleBase = GetModule(ModuleType::Motor);
	}
	else if constexpr (std::is_same_v<ModuleClass, CModuleDrill>)
	{
		moduleBase = GetModule(ModuleType::FuelTank);
	}
	else if constexpr (std::is_same_v<ModuleClass, CModuleCargo>)
	{
		moduleBase = GetModule(ModuleType::Cargo);
	}
	else if constexpr (std::is_same_v<ModuleClass, CModuleFuelTank>)
	{
		moduleBase = GetModule(ModuleType::FuelTank);
	}
	else
	{
		UNKNOWN_MODULE_CLASS;
	}

	return static_cast<ModuleClass*>(moduleBase);
}

/////////////////////////////////////////////////////////////////////////////

} // hvgs
