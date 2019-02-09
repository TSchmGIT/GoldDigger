#pragma once
#include "GameSessionNew/Actor/Economy/EconomyTypes.h"
#include "GameSessionNew/Actor/Equipment/Modules/DefinesModules.h"
#include "GameSessionNew/UI/Elements/UIButton.h"
#include "GameSessionNew/UI/Elements/UISpriteWithText.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{
class CBaseScene;
}

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui::BuildingWorkshop
{

/////////////////////////////////////////////////////////////////////////////

class CModuleElement
{
public:
	enum class ModulePurchaseState
	{
		Free,
		Equipped,
		Owned,
		ForSale
	};

public:
	CModuleElement() = default;
	virtual ~CModuleElement() = default;

public:
	CModuleElement(const CBaseScene& baseScene);

	void Draw() const;

	CUIButton& GetIconButton();
	const CUIButton& GetIconButton() const;

public:
	const Vector2& GetPosition() const;
	void SetPosition(const ScreenPos& position);

	TextureName GetModuleTexture() const;
	void SetModuleTexture(TextureName moduleTexture);

	ModulePurchaseState GetModuleState() const;
	void SetModuleState(ModulePurchaseState state);

	MoneyAmount GetModulePrice() const;
	void SetModulePrice(MoneyAmount name);

private:
	void UpdatePositions();
	void UpdateStateWidget();

private:
	Vector2 m_Position;

	CUIButton			m_IconButton;
	CUISpriteWithText	m_StateWidget;

	ModulePurchaseState m_ModuleState = ModulePurchaseState::Free;
	MoneyAmount			m_ModuleCosts = MoneyAmount(0);
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui::BuildingWorkshop
