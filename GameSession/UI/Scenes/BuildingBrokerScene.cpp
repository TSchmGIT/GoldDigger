#include "stdafx.h"
#include "BuildingBrokerScene.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemBase.h"
#include "GameSession/Items/ItemStack.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/UIButton.h"
#include "GameSession/World/World.h"
#include "Meta/SceneManager.h"
#include "Buildings/BuildingBroker.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

CBuildingBrokerScene::CBuildingBrokerScene()
{
	m_SellAllButton->SetPosition({ 1028.0f, 477.0f });
	m_SellAllButton->SetSize({ 405.0f, 63.0f });
	m_SellAllButton->SetAction(boost::bind(&CBuildingBrokerScene::OnSellAllButtonPressed, this));

	m_ExitButton->SetPosition({ 1028.0f, 669.0f });
	m_ExitButton->SetSize({ 405.0f, 63.0f });
	m_ExitButton->SetAction(boost::bind(&CBuildingBrokerScene::OnExitButtonPressed, this));
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
	hvgs::ScreenPos spriteScreenPos = hvgs::CRenderManager::Get().GetScreenCenter();
	hvgs::CRenderManager::GetMutable().DrawSprite(spriteScreenPos, hvgs::TextureName::SCENEBUILDINGBROKER);

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

		CRenderManager::GetMutable().DrawText(textPos, std::to_string(amount), Alignment::BottomRight, FontName::Courier_New, 40, sf::Color::White);
	}
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::DrawInteractionButtons() const
{
	// Sell button
	m_SellAllButton->Draw();
	CRenderManager::GetMutable().DrawText(m_SellAllButton->GetPosition() + m_SellAllButton->GetSize() * 0.5f, "Sell all", Alignment::Center, FontName::Arial, 50U);

	// Exit button
	m_ExitButton->Draw();
	CRenderManager::GetMutable().DrawText(m_ExitButton->GetPosition() + m_SellAllButton->GetSize() * 0.5f, "Exit", Alignment::Center, FontName::Arial, 50U);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::Enter()
{
	UpdateInventory();
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBrokerScene::OnSellAllButtonPressed()
{
	const auto* buildingBroker = CWorld::Get()->GetBuilding<CBuildingBroker>();
	ASSERT_OR_EXECUTE(buildingBroker, return);

	buildingBroker->PerformTransactionBuy(CWorld::GetMutable()->GetActor());

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
	const auto& actor = hvgs::CWorld::Get()->GetActor();
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

		const int slotsPerRow = 7;
		int coloum = i % slotsPerRow;
		int row = i / slotsPerRow;

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

} // hvgs::ui
