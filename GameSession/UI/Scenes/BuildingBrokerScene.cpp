#include "stdafx.h"
#include "BuildingBrokerScene.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Buildings/BuildingBroker.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemBase.h"
#include "GameSession/Items/ItemStack.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/Rendering/TextureManager.h"
#include "GameSession/Rendering/RenderDefines.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/Elements/UIButton.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CBuildingBrokerScene::CBuildingBrokerScene()
{
	m_SellAllButton->SetPosition({ 612.0f, 201.0f });
	m_SellAllButton->SetSize({ 405.0f, 63.0f });
	m_SellAllButton->SetAction(std::bind(&CBuildingBrokerScene::OnSellAllButtonPressed, this));
	m_SellAllButton->SetText("Sell All");
	m_SellAllButton->SetTextSize(FontSize(50));

	m_ExitButton->SetPosition({ 612.0f, 393.0f });
	m_ExitButton->SetSize({ 405.0f, 63.0f });
	m_ExitButton->SetAction(std::bind(&CBuildingBrokerScene::OnExitButtonPressed, this));
	m_ExitButton->SetText("Exit");
	m_ExitButton->SetTextSize(FontSize(50));
}

//////////////////////////////////////////////////////////////////////////

CBuildingBrokerScene::~CBuildingBrokerScene()
{

}

//////////////////////////////////////////////////////////////////////////

hvgs::ui::SceneID CBuildingBrokerScene::GetSceneID() const
{
	return SceneID::BuildingBroker;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::Draw() const
{
	// Draw main sprite
	hvgs::CRenderManager::GetMutable().DrawSpriteUI({ 0.0f, 0.0f }, hvgs::TextureName::SCENEBUILDINGBROKER, Alignment::TopLeft);

	// Fill scene with elements
	DrawInventory();
	DrawInteractionButtons();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::DrawInventory() const
{
	// Draw inventory slot buttons 
	for (const auto& pair : m_InventorySlotButtonList)
	{
		const auto& button = pair.first;
		int amount = pair.second;

		ASSERT_OR_EXECUTE(button, continue);
		button->Draw();

		ScreenPos textPos = button->GetPosition() + button->GetSize() - ScreenPos(2.0f, 2.0f); // Bottom right of button tile

		CRenderManager::GetMutable().DrawText(textPos, std::to_string(amount), Alignment::BottomRight, FontName::Courier_New, FontSize(40), sf::Color::White);
	}
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::DrawInteractionButtons() const
{
	m_SellAllButton->Draw();
	m_ExitButton->Draw();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::Enter()
{
	UpdateInventory();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::OnSellAllButtonPressed()
{
	const auto* buildingBroker = CWorld::Get().GetBuilding<CBuildingBroker>();
	ASSERT_OR_EXECUTE(buildingBroker, return);

	buildingBroker->PerformTransactionBuy(CWorld::GetMutable().GetActor());

	UpdateInventory();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::OnExitButtonPressed()
{
	CSceneManager::GetMutable().LeaveState(SceneID::BuildingBroker);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::UpdateInventory()
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
		const int slotsPerRow = 7;
		int coloum = i % slotsPerRow;
		int row = i / slotsPerRow;

		float x = 60.0f * coloum; // Offset per inventory element
		float y = 60.0f * row;
		Vector2 pos{ x, y };
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

bool CBuildingBrokerScene::IsFullscreenMenu() const
{
	return true;
}

//////////////////////////////////////////////////////////////////////////

hvgs::ScreenPos CBuildingBrokerScene::GetPivotPoint() const
{
	const auto& screenCenter = CRenderManager::Get().GetScreenCenter();
	const auto* texture = CTextureManager::Get().GetTexture(TextureName::SCENEBUILDINGBROKER);
	ASSERT_OR_EXECUTE(texture, return Vector2());

	auto textureSize = texture->getSize();
	hvmath::Vector2 textureSizeHalf{ textureSize.x * 0.5f, textureSize.y * 0.5f };

	auto pivotPoint = screenCenter - textureSizeHalf;
	return pivotPoint;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
