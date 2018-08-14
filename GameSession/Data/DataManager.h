#pragma once
#include <fstream>

#include "GameSession/Manager/SingletonBase.h"

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

class CDataManager : public hvgs::CSingletonBase<CDataManager>
{

public:
	CDataManager() = default;
	virtual ~CDataManager() = default;


public:
	void Init();

public:
	template<typename T>
	constexpr const T* GetModuleTemplate(ModuleGUID moduleGUID) const;

protected:
	template<class T>
	void LoadModuleList(const hvgs::String& fileName, hvgs::Map<ModuleGUID, T>& moduleMap);

protected:
	hvgs::Map<ModuleGUID, CDataTemplateModuleHull>		m_ModuleHullMap;
	hvgs::Map<ModuleGUID, CDataTemplateModuleFuelTank>	m_ModuleFuelTankMap;
	hvgs::Map<ModuleGUID, CDataTemplateModuleDrill>		m_ModuleDrillMap;
	hvgs::Map<ModuleGUID, CDataTemplateModuleCargo>		m_ModuleCargoMap;
	hvgs::Map<ModuleGUID, CDataTemplateModuleMotor>		m_ModuleMotorMap;
};

//////////////////////////////////////////////////////////////////////////

template<class T>
void hvda::CDataManager::LoadModuleList(const hvgs::String& fileName, hvgs::Map<ModuleGUID, T>& moduleMap)
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
		T moduleTemplate{ element };
		auto guid = moduleTemplate.GetGUID();

		// Save to map
		moduleMap.emplace(guid, std::move(moduleTemplate));
	}
}

/////////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr const T* hvda::CDataManager::GetModuleTemplate(ModuleGUID moduleGUID) const
{
	auto findLambda = [moduleGUID](const auto& moduleMap) -> const T*
	{
		auto itFind = moduleMap.find(moduleGUID);
		if (itFind == moduleMap.end())
		{
			ASSERT_TEXT(false, "Tried to get a module template, but guid was not found!");
			return nullptr;
		}

		return &itFind->second;
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
