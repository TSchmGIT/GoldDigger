#pragma once
#include "GameSession/UI/Scenes/BaseScene.h"
#include "GameSession/UI/Scenes/Meta/SceneEnum.h"

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

	virtual SceneID GetSceneID() const override;
	virtual bool IsFullscreenMenu() const override;

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
