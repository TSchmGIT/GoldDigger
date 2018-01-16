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

class CBuildingBrokerScene : public CBaseScene
{
public:
	CBuildingBrokerScene();
	virtual ~CBuildingBrokerScene();

	virtual SceneID GetSceneID() const override;

protected:
	virtual void Enter() override;

protected:
	virtual void Draw() const override;
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

	UniquePtr<CUIButton>	m_SellAllButton = std::make_unique<CUIButton>();
	UniquePtr<CUIButton>	m_ExitButton = std::make_unique<CUIButton>();
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
