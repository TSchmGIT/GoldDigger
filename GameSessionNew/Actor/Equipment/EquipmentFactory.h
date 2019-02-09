#pragma once

#include "GameSessionNew/Manager/SingletonBase.h"

#include "GameSessionNew/Actor/Equipment/Modules/EnumsModules.h"
#include "GameSessionNew/Actor/Equipment/Modules/ModuleBase.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{
class CModuleBase;
class CEquipment;
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
	ModulePtr CreateDefaultModule(ModuleType moduleType, CEquipment& parentEquipment);
	ModulePtr CreateModule(ModuleType moduleType, ModuleGUID moduleGUID, CEquipment& parentEquipment, Optional<const CModuleBase&> inheritedModule);

protected:
	void DestroyModule(CModuleBase* moduleInstance);

	template<class ModuleClass, class ModuleTemplate>
	ModulePtr CreateModule(ModuleGUID guid, CEquipment& parentEquipment, Optional<const ModuleClass&> inheritedModule)
	{
		const auto*	moduleTemplate = hvda::CDataModuleManager::Get().GetModuleTemplate<ModuleTemplate>(guid);
		ASSERT_OR_EXECUTE(moduleTemplate, return ModulePtr(nullptr, nullptr));

		// Create new module of specific type
		auto boundDeleter = [this](CModuleBase* moduleBase) { DestroyModule(moduleBase); };
		ModulePtr moduleInstance(new ModuleClass(m_UniqueModuleID, parentEquipment, *moduleTemplate, inheritedModule), boundDeleter);

		// Emplace it in the map
		auto emplaceResult = m_ModuleInstanceMap.emplace(m_UniqueModuleID, moduleInstance.get());
		ASSERT_OR_EXECUTE(emplaceResult.second, return ModulePtr(nullptr, nullptr));

		// Increase unique ID
		m_UniqueModuleID += ModuleID(1);

		// Return unique ptr
		return std::move(moduleInstance);
	}

	Map<ModuleID, CModuleBase*> m_ModuleInstanceMap;
	ModuleID m_UniqueModuleID = ModuleID(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
