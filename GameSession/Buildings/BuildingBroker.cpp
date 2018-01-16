#include "stdafx.h"
#include "BuildingBroker.h"

#include "GameSession/Actor/Actor.h"
#include "GameSession/Actor/Economy/ActorEconomy.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemStack.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/Scenes/Meta/SceneEnum.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"
#include "GameSession/World/World.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CBuildingBroker::CBuildingBroker()
{
	m_InteractionDistance = 2.5f;
	m_Texture = TextureName::BUILDING_BROKER;
	m_Size = { 3.0f, 3.0f };

	FillPriceChart();
}

//////////////////////////////////////////////////////////////////////////

bool CBuildingBroker::IsInInteractionDistance(const WorldPos& position) const
{
	return Vector2::DistanceCheck(position, m_Position, m_InteractionDistance);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBroker::StartInteraction()
{
	ui::CSceneManager::GetMutable().EnterState(ui::SceneID::BuildingBroker);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBroker::StopInteraction()
{
	ui::CSceneManager::GetMutable().LeaveState(ui::SceneID::BuildingBroker);
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CBuildingBroker::GetInteractionButtonPosition() const 
{
	return m_Position + WorldPos(0.0f, GetAABBHalfs().y);
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBroker::PerformTransactionBuy(CActor& actor) const
{
	auto& economy = actor.GetEconomy();
	auto& inventory = actor.GetInventory();

	// Calculate and add money to the economy
	MoneyAmount reward;
	for (const auto& itemStack : inventory.GetStackList())
	{
		reward += GetPrice(itemStack->GetTileType()) * MoneyAmount(itemStack->GetCurrentAmount());
	}
	economy.AddMoney(reward);

	// Remove all items from inventory
	inventory.RemoveAllItems();
}

//////////////////////////////////////////////////////////////////////////

hvgs::MoneyAmount CBuildingBroker::GetPrice(TileType tileType) const
{
	auto it = m_PriceChart.find(tileType);
	ASSERT_OR_EXECUTE(it != m_PriceChart.end(), return MoneyAmount(0));

	return it->second;
}

//////////////////////////////////////////////////////////////////////////

void CBuildingBroker::FillPriceChart()
{
	for (int i = 0; i < int(TileType::Count); i++)
	{
		auto tileType = TileType(i);
		MoneyAmount price;

		switch (tileType)
		{
		case hvgs::TileType::Grass:
			price = MoneyAmount(20);
			break;
		case hvgs::TileType::Dirt:
			price = MoneyAmount(10);
			break;
		case hvgs::TileType::Stone:
			price = MoneyAmount(30);
			break;
		case hvgs::TileType::IronOre:
			price = MoneyAmount(100);
			break;
		case hvgs::TileType::GoldOre:
			price = MoneyAmount(330);
			break;
		}

		m_PriceChart[tileType] = price;
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::WorldPos& CBuildingBroker::GetInteractionOriginPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
