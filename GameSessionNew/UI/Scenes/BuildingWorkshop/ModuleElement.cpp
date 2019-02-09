#include "stdafx.h"
#include "ModuleElement.h"

#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"
#include "GameSessionNew/UI/UIStructs.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui::BuildingWorkshop
{

//////////////////////////////////////////////////////////////////////////

CModuleElement::CModuleElement(const CBaseScene& baseScene)
	: m_IconButton(baseScene)
	, m_StateWidget(TextureName::BUTTON_DEFAULT, TextUIInfo())
{
	UpdatePositions();
	UpdateStateWidget();
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::Draw() const
{
	m_IconButton.Draw();
	m_StateWidget.Draw();
}

//////////////////////////////////////////////////////////////////////////

const hvgs::Vector2& CModuleElement::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::SetPosition(const ScreenPos& position)
{
	if (m_Position == position)
	{
		return;
	}

	m_Position = position;
	UpdatePositions();
}

//////////////////////////////////////////////////////////////////////////

hvgs::TextureName CModuleElement::GetModuleTexture() const
{
	return m_IconButton.GetTextureForState(ButtonState::Default);
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::SetModuleTexture(TextureName moduleTexture)
{
	m_IconButton.SetTextureForAllStates(moduleTexture);
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::BuildingWorkshop::CModuleElement::ModulePurchaseState CModuleElement::GetModuleState() const
{
	return m_ModuleState;
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::SetModuleState(ModulePurchaseState state)
{
	if (m_ModuleState == state)
	{
		return;
	}

	m_ModuleState = state;

	UpdateStateWidget();
}

//////////////////////////////////////////////////////////////////////////

hvgs::MoneyAmount CModuleElement::GetModulePrice() const
{
	return m_ModuleCosts;
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::SetModulePrice(MoneyAmount name)
{
	if (m_ModuleCosts == name)
	{
		return;
	}

	m_ModuleCosts = name;
	UpdateStateWidget();
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::UpdateStateWidget()
{
	m_StateWidget.SetTextSize(FontSize(23));

	switch (m_ModuleState)
	{
	case hvgs::ui::BuildingWorkshop::CModuleElement::ModulePurchaseState::Free:
		m_StateWidget.SetText("FREE");
		break;
	case hvgs::ui::BuildingWorkshop::CModuleElement::ModulePurchaseState::Owned:
		m_StateWidget.SetText("OWNED");
		break;
	case hvgs::ui::BuildingWorkshop::CModuleElement::ModulePurchaseState::Equipped:
		m_StateWidget.SetText("EQUIPPED");
		break;
	case hvgs::ui::BuildingWorkshop::CModuleElement::ModulePurchaseState::ForSale:
		auto moduleCostsString = std::to_string(m_ModuleCosts.get());
		m_StateWidget.SetText(moduleCostsString);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

void CModuleElement::UpdatePositions()
{
	m_IconButton.SetPosition(m_Position);
	m_IconButton.SetSize({ 124.0f, 124.0f });

	constexpr ScreenPos offset{ 0.0f, 124.0f };
	m_StateWidget.SetPosition(m_Position + offset);
	m_StateWidget.SetSize({ 124.0f, 29.0f });
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::CUIButton& CModuleElement::GetIconButton()
{
	return m_IconButton;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::ui::CUIButton& CModuleElement::GetIconButton() const
{
	return m_IconButton;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui::BuildingWorkshop
