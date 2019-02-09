#pragma once
#include "GameSessionNew/UI/Scenes/BaseScene.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneEnum.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
class CUIButton;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class CInventoryScene : public CBaseScene
{

public:
	CInventoryScene();
	virtual ~CInventoryScene();

	SceneID GetSceneID() const override;
	bool IsFullscreenMenu() const override;

	ScreenPos GetPivotPoint() const override;

public:
	virtual void Draw() const override;

public:
	virtual void Enter() override;

	virtual void SyncTick() override;



protected:
	Vector<std::pair<UniquePtr<CUIButton>, int>> m_InventorySlotButtonList;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
