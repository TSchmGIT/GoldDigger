#pragma once
#include <fstream>

#include "GameSession/Manager/SingletonBase.h"

#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleBase.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleCargo.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleDrill.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleFuelTank.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleHull.h"
#include "GameSession/Actor/Equipment/Modules/DataTemplates/DataTemplateModuleMotor.h"
#include "GameSession/Data/DataDefines.h"

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

/////////////////////////////////////////////////////////////////////////////

class CDataModuleManager : public hvgs::CSingletonBase<CDataModuleManager>
{

public:
	CDataModuleManager() = default;
	virtual ~CDataModuleManager() = default;


public:
	void Init();

public:
	template<typename T>
	constexpr const T* GetModuleTemplate(ModuleGUID moduleGUID) const;

protected:
	template<class T>
	void LoadModuleList(const hvgs::String& fileName, hvgs::Map<ModuleGUID, hvgs::UniquePtr<T>>& moduleMap);

	//template<enum moduleType>
	//constexpr const hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleBase>>& GetModuleList() const;

protected:
	hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleHull>>			m_ModuleHullMap;
	hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleMotor>>		m_ModuleMotorMap;
	hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleDrill>>		m_ModuleDrillMap;
	hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleCargo>>		m_ModuleCargoMap;
	hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleFuelTank>>		m_ModuleFuelTankMap;
};

//////////////////////////////////////////////////////////////////////////

//template<enum moduleType>
//constexpr const hvgs::Map<ModuleGUID, hvgs::UniquePtr<CDataTemplateModuleBase>>& hvda::CDataModuleManager::GetModuleList() const
//{
//	//if constexpr (moduleType == ModuleType::Hull)
//	//{
//	//	return m_ModuleHullMap;
//	//}
//	//else if constexpr (moduleType == ModuleType::Motor)
//	//{
//	//	return m_ModuleMotorMap;
//	//}
//	//else if constexpr (moduleType == ModuleType::Drill)
//	//{
//	//	return m_ModuleDrillMap;
//	//}
//	//else if constexpr (moduleType == ModuleType::Cargo)
//	//{
//	//	return m_ModuleCargoMap;
//	//}
//	//else if constexpr (moduleType == ModuleType::FuelTank)
//	//{
//	//	return m_ModuleFuelTankMap;
//	//}
//
//	return m_ModuleCargoMap;
//}

//////////////////////////////////////////////////////////////////////////

template<class T>
void hvda::CDataModuleManager::LoadModuleList(const hvgs::String& fileName, hvgs::Map<ModuleGUID, hvgs::UniquePtr<T>>& moduleMap)
{
	moduleMap.clear();

	// Load json string
	auto dataPath = hvgs::String(R"(..\Resources\Data\)");
	auto fileNameFull = dataPath.append(fileName);
	std::ifstream ifs(fileNameFull);

	// Parse to json object
	json j = json::parse(ifs);

	// Iterate elements of json
	for (auto& element : j)
	{
		// Convert to module objects
		hvgs::UniquePtr<T> moduleTemplate = std::make_unique<T>(element);
		auto guid = moduleTemplate->GetGUID();

		// Save to map
		moduleMap.emplace(guid, std::move(moduleTemplate));
	}
}

/////////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr const T* hvda::CDataModuleManager::GetModuleTemplate(ModuleGUID moduleGUID) const
{
	auto findLambda = [moduleGUID](const auto& moduleMap) -> const T*
	{
		auto itFind = moduleMap.find(moduleGUID);
		if (itFind == moduleMap.end())
		{
			ASSERT_TEXT(false, "Tried to get a module template, but guid was not found!");
			return nullptr;
		}

		return itFind->second.get();
	};

	if constexpr (std::is_same_v<T, CDataTemplateModuleHull>)
	{
		return findLambda(m_ModuleHullMap);
	}
	else if constexpr (std::is_same_v<T, CDataTemplateModuleMotor>)
	{
		return findLambda(m_ModuleMotorMap);
	}
	else if constexpr (std::is_same_v<T, CDataTemplateModuleDrill>)
	{
		return findLambda(m_ModuleDrillMap);
	}
	else if constexpr (std::is_same_v<T, CDataTemplateModuleCargo>)
	{
		return findLambda(m_ModuleCargoMap);
	}
	else if constexpr (std::is_same_v<T, CDataTemplateModuleFuelTank>)
	{
		return findLambda(m_ModuleFuelTankMap);
	}
	else
	{
		UNKNOWN_MODULE_TYPE;
	}
}


//////////////////////////////////////////////////////////////////////////

} // hvda
