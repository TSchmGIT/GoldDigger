#include "stdafx.h"
#include "InventoryScene.h"

#include "GameSessionNew/Actor/Actor.h"
#include "GameSessionNew/Items/Inventory.h"
#include "GameSessionNew/Items/ItemBase.h"
#include "GameSessionNew/Items/ItemStack.h"
#include "GameSessionNew/Manager/RenderManager.h"
#include "GameSessionNew/Manager/Rendering/TextureManager.h"
#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"
#include "GameSessionNew/UI/Elements/UIButton.h"
#include "GameSessionNew/World/World.h"

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
		auto& itemButton = m_InventorySlotButtonList.emplace_back(std::make_unique<CUIButton>(*this), itemStack.GetCurrentAmount());

		// Update texture
		const auto* item = itemStack.GetFirstItem();
		ASSERT_OR_EXECUTE(item, continue); //< item stacks in the inventory must have items in their stack

		itemButton.first->SetTextureForState(ButtonState::Default, item->GetTextureName());

		// Update position
		int coloum = i % 16;
		int row = i / 16;

		float x = 60.0f * coloum; // Offset per inventory element
		float y = 60.0f * row;
		ScreenPos pos{ x, y };
		ScreenPos offset{ 70.0f, 195.0f };
		pos += offset;

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

hvgs::ScreenPos CInventoryScene::GetPivotPoint() const
{
	const auto* texture = CTextureManager::Get().GetTexture(TextureName::INVENTORYMAINSPRITE);
	ASSERT_OR_EXECUTE(texture, return Vector2());

	auto textureSize = texture->getSize();
	Vector2 textureSizeHalf{ textureSize.x * 0.5f, textureSize.y * 0.5f };

	auto pivotPoint = CRenderManager::GetBaseScreenSize() * 0.5f - textureSizeHalf;
	return pivotPoint;
}

//////////////////////////////////////////////////////////////////////////

void CInventoryScene::Draw() const
{
	// Draw inventory sprite
	hvgs::CRenderManager::GetMutable().DrawSpriteUI({ 0.0f, 0.0f }, hvgs::TextureName::INVENTORYMAINSPRITE, Alignment::TopLeft);

	// Draw inventory slot buttons 
	for (const auto& pair : m_InventorySlotButtonList)
	{
		const auto& button = pair.first;
		int amount = pair.second;

		ASSERT_OR_EXECUTE(button, continue);
		button->Draw();

		ScreenPos textPos = button->GetPosition() + button->GetSize() - ScreenPos(2.0f, 2.0f); // Bottom right of button tile

		CRenderManager::GetMutable().DrawTextUI(textPos, std::to_string(amount), Alignment::BottomRight, FontName::Courier_New, FontSize(40), sf::Color::White);
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
