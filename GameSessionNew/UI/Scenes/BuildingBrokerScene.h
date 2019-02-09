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

class CBuildingBrokerScene : public CBaseScene
{
public:
	CBuildingBrokerScene();
	virtual ~CBuildingBrokerScene();

	SceneID GetSceneID() const override;
	bool IsFullscreenMenu() const override;

	ScreenPos GetPivotPoint() const override;

protected:
	void Enter() override;

protected:
	void Draw() const override;
	void DrawInventory() const;
	void DrawInteractionButtons() const;

	void UpdateInventory();

protected:
	//////////////////////////////////////////////////////////////////////////
	// Button Actions
	void OnSellAllButtonPressed();
	void OnExitButtonPressed();

protected:
	Vector<std::pair<UniquePtr<CUIButton>, int>> m_InventorySlotButtonList;

	UniquePtr<CUIButton>	m_SellAllButton = std::make_unique<CUIButton>(*this);
	UniquePtr<CUIButton>	m_ExitButton = std::make_unique<CUIButton>(*this);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
