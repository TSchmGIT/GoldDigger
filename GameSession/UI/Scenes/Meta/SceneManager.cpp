#include "stdafx.h"
#include "SceneManager.h"
#include "GameSession/UI/Scenes/InventoryScene.h"
#include "GameSession/UI/Scenes/BuildingBrokerScene.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CSceneManager::CSceneManager()
{

}

//////////////////////////////////////////////////////////////////////////

CSceneManager::~CSceneManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::SyncTick()
{
	for (auto& sceneData : m_sceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		sceneData.Scene->SyncTick();
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::Draw() const
{
	for (const auto& sceneData : m_sceneDataList)
	{
		if (!sceneData.IsShown)
		{
			continue;
		}

		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		sceneData.Scene->DrawBase();
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::Init()
{
	m_sceneDataList.push_back({ std::make_unique<CInventoryScene>(), false });
	m_sceneDataList.push_back({ std::make_unique<CBuildingBrokerScene>(), false });
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::EnterState(SceneID sceneID)
{
	for (auto& sceneData : m_sceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		if (sceneData.Scene->GetSceneID() != sceneID)
		{
			continue;
		}


		bool oldIsShown = sceneData.IsShown;
		sceneData.IsShown = true;

		if (!oldIsShown)
		{
			sceneData.Scene->EnterBase();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::LeaveState(SceneID sceneID)
{
	for (auto& sceneData : m_sceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		if (sceneData.Scene->GetSceneID() != sceneID)
		{
			continue;
		}

		sceneData.IsShown = false;

		bool oldIsShown = sceneData.IsShown;
		sceneData.IsShown = false;

		if (oldIsShown)
		{
			sceneData.Scene->ExitBase();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::ToggleState(SceneID sceneID)
{
	for (auto& sceneData : m_sceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		if (sceneData.Scene->GetSceneID() != sceneID)
		{
			continue;
		}

		sceneData.IsShown = !sceneData.IsShown;

		if (sceneData.IsShown)
		{
			sceneData.Scene->EnterBase();
		}
		else
		{
			sceneData.Scene->ExitBase();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
