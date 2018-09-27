#include "stdafx.h"
#include "BuildingWorkshopSceneBase.h"

#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/Rendering/TextureManager.h"
#include "GameSession/Rendering/UIScope.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

hvgs::Vector2 CBuildingWorkshopSceneBase::GetPivotPoint() const
{
	const auto& screenCenter = CRenderManager::Get().GetScreenCenter();
	const auto* texture = CTextureManager::Get().GetTexture(TextureName::BUILDING_WORKSHOP);
	ASSERT_OR_EXECUTE(texture, return Vector2());

	auto textureSize = texture->getSize();
	hvmath::Vector2 textureSizeHalf{ textureSize.x * 0.5f, textureSize.y * 0.5f };

	auto pivotPoint = screenCenter - textureSizeHalf;
	return pivotPoint;
}

//////////////////////////////////////////////////////////////////////////

BuildingWorkshop::CCategorySelectionList& CBuildingWorkshopSceneBase::GetCategoryButtonList()
{
	return m_CategoryButtonList;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingWorkshopSceneBase::Draw() const
{
	DrawBackground();

	DrawCategorySelection();
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

	const auto& screenCenter = CRenderManager::Get().GetScreenCenter();
	const auto* texture = CTextureManager::Get().GetTexture(TextureName::BUILDING_WORKSHOP);
	ASSERT_OR_EXECUTE(texture, return);

	auto textureSize = texture->getSize();
	hvmath::Vector2 textureSizeHalf{ textureSize.x * 0.5f, textureSize.y * 0.5f };

	auto pivotPoint = screenCenter - textureSizeHalf;
	//m_CategoryButtonList.SetPivotPos(pivotPoint);
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

}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
