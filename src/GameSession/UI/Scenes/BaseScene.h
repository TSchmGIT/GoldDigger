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
	virtual bool IsFullscreenMenu() const = 0;

	virtual ScreenPos GetPivotPoint() const = 0;
	ScreenPos GetPivotPointGlobal() const;


public:
	virtual void Init() {};

	void EnterBase();
	void ExitBase();

	virtual bool OnCustomEscHandling();

	void DrawBase();

	bool IsShown() const;
	
protected:

	virtual void Enter() {};
	virtual void Exit() {};

	virtual void Draw() const = 0;


public:

	virtual void OnEnterState() {};

	virtual void SyncTick() {}
	virtual void SyncTickVisible() {}

private:
	bool	m_IsShown = false;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
