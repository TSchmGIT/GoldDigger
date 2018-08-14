#pragma once

#include "GameSession/Manager/SingletonBase.h"

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

class CEquipmentFactory : public CSingletonBase<CEquipmentFactory>
{

public:
	CEquipmentFactory() = default;
	virtual ~CEquipmentFactory() = default;

public:
	WeakPtr<CModuleBase> CreateDefaultModule(ModuleType moduleType);
	WeakPtr<CModuleBase> CreateModule(ModuleType moduleType, ModuleGUID moduleGUID);

protected:
	template<class ModuleClass, class ModuleTemplate>
	WeakPtr<CModuleBase> CreateModule(ModuleGUID guid)
	{
		const auto*	moduleTemplate = hvda::CDataManager::Get().GetModuleTemplate<ModuleTemplate>(guid);
		ASSERT_OR_EXECUTE(moduleTemplate, return hvgs::WeakPtr<hvgs::CModuleBase>());

		// Create new module of specific type
		auto moduleInstance = std::make_shared<ModuleClass>(m_UniqueModuleID, *moduleTemplate);

		// Emplace it in the map
		auto emplaceResult = m_ModuleInstanceMap.emplace(m_UniqueModuleID, moduleInstance);
		ASSERT_OR_EXECUTE(emplaceResult.second, return hvgs::WeakPtr<hvgs::CModuleBase>());

		// Increase unique ID
		m_UniqueModuleID += ModuleID(1);

		// Return weak ptr
		return hvgs::WeakPtr<CModuleBase>(std::move(moduleInstance));
	}

	Map<ModuleID, SharedPtr<CModuleBase>> m_ModuleInstanceMap;
	ModuleID m_UniqueModuleID = ModuleID(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
