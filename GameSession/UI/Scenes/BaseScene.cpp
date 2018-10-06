#include "stdafx.h"
#include "BaseScene.h"

#include "GameSession/Rendering/UIScope.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CBaseScene::CBaseScene()
{

}

//////////////////////////////////////////////////////////////////////////

CBaseScene::~CBaseScene()
{

}

//////////////////////////////////////////////////////////////////////////

void CBaseScene::EnterBase()
{
	m_IsShown = true;

	Enter();
}

//////////////////////////////////////////////////////////////////////////

void CBaseScene::ExitBase()
{
	m_IsShown = false;

	Exit();
}

//////////////////////////////////////////////////////////////////////////

void CBaseScene::DrawBase()
{
	if (!m_IsShown)
	{
		return;
	}

	CUIScope uiScope(GetPivotPoint());
	Draw();
}

//////////////////////////////////////////////////////////////////////////

bool CBaseScene::IsShown() const
{
	return m_IsShown;
}

//////////////////////////////////////////////////////////////////////////

bool CBaseScene::OnCustomEscHandling()
{
	CSceneManager::GetMutable().LeaveState(GetSceneID());

	return true;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ScreenPos CBaseScene::GetPivotPointGlobal() const
{
	auto pivotPointGlobal = GetPivotPoint();
	CRenderManager::Get().ScaleUIPos(pivotPointGlobal);

	return pivotPointGlobal;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
