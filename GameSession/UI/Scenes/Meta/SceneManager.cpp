#include "stdafx.h"
#include "SceneManager.h"

#include "GameSession/Manager/InputManager.h"
#include "GameSession/UI/Scenes/BuildingBrokerScene.h"
#include "GameSession/UI/Scenes/BuildingWorkshop/BuildingWorkshopScene.h"
#include "GameSession/UI/Scenes/InventoryScene.h"

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
	for (auto& sceneData : m_SceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		sceneData.Scene->SyncTick();
	}

	// Esc handling
	if (bool escPressedDown = CInputManager::Get().GetButtonDown(Button::Cancel);
	escPressedDown && IsFullscreenMenuVisble())
	{
		for (const auto& sceneData : m_SceneDataList)
		{
			if (!sceneData.IsShown)
			{
				continue;
			}

			sceneData.Scene->OnCustomEscHandling();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::Draw() const
{
	for (const auto& sceneData : m_SceneDataList)
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
	m_SceneDataList.push_back({ std::make_unique<CInventoryScene>(), false });
	m_SceneDataList.push_back({ std::make_unique<CBuildingBrokerScene>(), false });
	m_SceneDataList.push_back({ std::make_unique<CBuildingWorkshopScene>(), false });
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::EnterState(SceneID sceneID)
{
	for (auto& sceneData : m_SceneDataList)
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
			// Track full screen visibility 
			if (sceneData.Scene->IsFullscreenMenu())
			{
				++m_FullScreenUIVisibile;
			}
			sceneData.Scene->EnterBase();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::LeaveState(SceneID sceneID)
{
	for (auto& sceneData : m_SceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		if (sceneData.Scene->GetSceneID() != sceneID)
		{
			continue;
		}

		bool oldIsShown = sceneData.IsShown;
		sceneData.IsShown = false;

		if (oldIsShown)
		{
			// Track full screen visibility 
			if (sceneData.Scene->IsFullscreenMenu())
			{
				--m_FullScreenUIVisibile;
				ASSERT(m_FullScreenUIVisibile >= 0);
			}

			sceneData.Scene->ExitBase();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CSceneManager::ToggleState(SceneID sceneID)
{
	for (auto& sceneData : m_SceneDataList)
	{
		ASSERT_OR_EXECUTE(sceneData.Scene, continue);
		if (sceneData.Scene->GetSceneID() != sceneID)
		{
			continue;
		}

		sceneData.IsShown = !sceneData.IsShown;

		if (sceneData.IsShown)
		{
			// Track full screen visibility 
			if (sceneData.Scene->IsFullscreenMenu())
			{
				++m_FullScreenUIVisibile;
			}
			sceneData.Scene->EnterBase();
		}
		else
		{
			// Track full screen visibility 
			if (sceneData.Scene->IsFullscreenMenu())
			{
				--m_FullScreenUIVisibile;
				ASSERT(m_FullScreenUIVisibile >= 0);
			}
			sceneData.Scene->ExitBase();
		}
	}
}

//////////////////////////////////////////////////////////////////////////

bool CSceneManager::IsFullscreenMenuVisble() const
{
	return m_FullScreenUIVisibile > 0;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
