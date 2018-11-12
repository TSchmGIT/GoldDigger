#include "stdafx.h"
#include "BuildingWorkshopSceneBase.h"

#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/Rendering/TextureManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CBuildingWorkshopSceneBase::CBuildingWorkshopSceneBase()
{
	m_ModuleList.SetMaximumElementsHorizontal(4);


}

//////////////////////////////////////////////////////////////////////////

hvgs::Vector2 CBuildingWorkshopSceneBase::GetPivotPoint() const
{
	const auto* texture = CTextureManager::Get().GetTexture(TextureName::BUILDING_WORKSHOP);
	ASSERT_OR_EXECUTE(texture, return Vector2());

	auto textureSize = texture->getSize();
	Vector2 textureSizeHalf{ textureSize.x * 0.5f, textureSize.y * 0.5f };

	auto pivotPoint = CRenderManager::GetBaseScreenSize() * 0.5f - textureSizeHalf;
	return pivotPoint;
}

//////////////////////////////////////////////////////////////////////////

BuildingWorkshop::CCategorySelectionList& CBuildingWorkshopSceneBase::GetCategoryButtonList()
{
	return m_CategoryButtonList;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::BuildingWorkshop::CModuleList& CBuildingWorkshopSceneBase::GetModuleList()
{
	return m_ModuleList;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::Draw() const
{
	DrawBackground();

	DrawCategorySelection();

	DrawModuleList();

	DrawModuleDetailView();

	DrawCloseButton();
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::SceneID CBuildingWorkshopSceneBase::GetSceneID() const
{
	return SceneID::BuildingWorkshop;
}

//////////////////////////////////////////////////////////////////////////

bool CBuildingWorkshopSceneBase::IsFullscreenMenu() const
{
	return true;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::SyncTick()
{
	CBaseScene::SyncTick();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::DrawBackground() const
{
	hvgs::CRenderManager::GetMutable().DrawSpriteUI(ScreenPos(), hvgs::TextureName::BUILDING_WORKSHOP, Alignment::TopLeft);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::DrawCategorySelection() const
{
	m_CategoryButtonList.Draw();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::DrawModuleList() const
{
	m_ModuleList.Draw();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::DrawModuleDetailView() const
{
	m_ModuleDetailPanel.Draw();
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::BuildingWorkshop::CModuleDetailPanel& CBuildingWorkshopSceneBase::GetModuleDetailPanel()
{
	return m_ModuleDetailPanel;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::Init()
{
	InitPurchaseButton();
	InitCloseButton();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::DrawCloseButton() const
{
	m_CloseButton.Draw();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::InitPurchaseButton()
{
	auto& purchaseButton = m_ModuleDetailPanel.GetPurchaseButton();
	purchaseButton.SetAction(boost::bind(&CBuildingWorkshopSceneBase::OnPurchaseButtonPressed, this));
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::InitCloseButton()
{
	constexpr ScreenPos		buttonPos{ 1529.0f, 17.0f };
	constexpr Vector2		buttonSize{ 51.0f, 52.0f };

	m_CloseButton.SetPosition(buttonPos);
	m_CloseButton.SetSize(buttonSize);
	m_CloseButton.SetTextureForAllStates(TextureName::BUILDING_WORKSHOP_UI_CLOSE_BUTTON);
	m_CloseButton.SetAction(boost::bind(&CBuildingWorkshopSceneBase::OnCloseButtonPressed, this));
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::CUIButton& CBuildingWorkshopSceneBase::GetCloseButton()
{
	return m_CloseButton;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
