#pragma once
#include "GameSessionNew/Manager/SingletonBase.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneEnum.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
class CBaseScene;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

struct SceneData
{
	UniquePtr<CBaseScene>	Scene;
	bool					IsShown;
};

class CSceneManager : public CSingletonBase<CSceneManager>
{

public:
	CSceneManager();
	virtual ~CSceneManager();

	void Init();

	void SyncTick();
	void Draw() const;

public:
	void EnterState(SceneID sceneID);
	void LeaveState(SceneID sceneID);
	void ToggleState(SceneID sceneID);

public:
	bool IsFullscreenMenuVisble() const;

protected:
	Vector<SceneData> m_SceneDataList;
	
	int			m_FullScreenUIVisibile = 0;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
