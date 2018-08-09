#include "stdafx.h"
#include "InventoryScene.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemBase.h"
#include "GameSession/Items/ItemStack.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/UIButton.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CInventoryScene::CInventoryScene()
{

}

//////////////////////////////////////////////////////////////////////////

CInventoryScene::~CInventoryScene()
{

}

//////////////////////////////////////////////////////////////////////////

void CInventoryScene::Enter()
{
	// Gather inventory data from actor
	const auto& actor = hvgs::CWorld::Get().GetActor();
	const auto& inventory = actor.GetInventory();

	int i = 0;

	m_InventorySlotButtonList.clear();
	for (const auto& itemStack : inventory.GetStackList())
	{
		auto& itemButton = m_InventorySlotButtonList.emplace_back(std::make_unique<CUIButton>(), itemStack->GetCurrentAmount());

		// Update texture
		const auto* item = itemStack->GetFirstItem();
		ASSERT_OR_EXECUTE(item, continue); //< item stacks in the inventory must have items in their stack

		itemButton.first->SetTextureForState(ButtonState::Default, item->GetTextureName());

		// Update position
		ScreenPos pos = ScreenPos(486.0f, 471.0f); // Top left of the inventory

		int coloum = i % 16;
		int row = i / 16;

		pos.x += 60.0f * coloum; // Offset per inventory element
		pos.y += 60.0f * row;
		itemButton.first->SetPosition(pos);

		// Update size
		itemButton.first->SetSize({ 52.0f, 52.0f });

		i++;
		if (i >= 16 * 5)
		{
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CInventoryScene::Draw() const
{

	// Draw inventory sprite
	hvgs::ScreenPos spriteScreenPos = hvgs::CRenderManager::Get().GetScreenCenter();
	hvgs::CRenderManager::GetMutable().DrawSprite(spriteScreenPos, hvgs::TextureName::INVENTORYMAINSPRITE);

	// Draw inventory slot buttons 
	for (const auto& pair : m_InventorySlotButtonList)
	{
		const auto& button = pair.first;
		int amount = pair.second;

		ASSERT_OR_EXECUTE(button, continue);
		button->Draw();

		ScreenPos textPos = button->GetPosition() + button->GetSize() - ScreenPos(2.0f, 2.0f); // Bottom right of button tile

		CRenderManager::GetMutable().DrawText(textPos, std::to_string(amount), Alignment::BottomRight, FontName::Courier_New, 40, sf::Color::White);
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::SceneID CInventoryScene::GetSceneID() const
{
	return SceneID::Inventory;
}

//////////////////////////////////////////////////////////////////////////

void CInventoryScene::SyncTick()
{
}

//////////////////////////////////////////////////////////////////////////

bool CInventoryScene::IsFullscreenMenu() const
{
	return true;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
