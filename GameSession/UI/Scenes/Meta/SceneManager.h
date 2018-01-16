#pragma once
#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/UI/Scenes/Meta/SceneEnum.h"

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

protected:
	Vector<SceneData> m_sceneDataList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
