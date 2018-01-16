#pragma once
#include "GameSession/Rendering/IRenderElement.h"
#include "GameSession/UI/Scenes/Meta/SceneEnum.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CBaseScene
{

public:
	CBaseScene();
	virtual ~CBaseScene();

	virtual SceneID GetSceneID() const = 0;

public:
	void EnterBase();
	void ExitBase();

	void DrawBase();

	bool IsShown() const;

protected:
	virtual void Enter() {};
	virtual void Exit() {};

	virtual void Draw() const = 0;

public:

	virtual void OnEnterState() {};

	virtual void SyncTick() {}

private:
	bool	m_IsShown = false;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
