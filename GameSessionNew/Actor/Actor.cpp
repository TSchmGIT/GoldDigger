#include "stdafx.h"
#include "Actor.h"

#include <hvmath/Physics/AABB.h>

#include "GameSessionNew/Actor/Economy/ActorEconomy.h"
#include "GameSessionNew/Actor/Equipment/Equipment.h"
#include "GameSessionNew/Actor/Health/ActorHealth.h"
#include "GameSessionNew/Actor/Interaction/IInteractionObject.h"
#include "GameSessionNew/Actor/Motor/MotorDefault.h"
#include "GameSessionNew/Actor/Motor/MotorDigging.h"
#include "GameSessionNew/Camera/Camera.h"
#include "GameSessionNew/Items/Inventory.h"
#include "GameSessionNew/Items/ItemBlock.h"
#include "GameSessionNew/Items/ItemStack.h"
#include "GameSessionNew/Manager/CameraManager.h"
#include "GameSessionNew/Manager/InputManager.h"
#include "GameSessionNew/Manager/InteractionManager.h"
#include "GameSessionNew/Manager/PhysicsManager.h"
#include "GameSessionNew/Manager/RenderManager.h"
#include "GameSessionNew/Manager/TimeManager.h"
#include "GameSessionNew/Physics/PhysicsEnums.h"
#include "GameSessionNew/Rendering/DebugRender.h"
#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneEnum.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneManager.h"
#include "GameSessionNew/World/Tile.h"
#include "GameSessionNew/World/World.h"
#include "Equipment/Modules/ModuleFuelTank.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{


////////////////////////////////////////////////////////////////////////////

CActor::CActor()
	: m_Health(std::make_unique<CActorHealth>())
	, m_Economy(std::make_unique<CActorEconomy>())
	, m_Inventory(std::make_unique<CInventory>())
	, m_Equipment(std::make_unique<CEquipment>(*this))
	, m_Motor(std::make_unique<CMotorDefault>(*this))
{
}

//////////////////////////////////////////////////////////////////////////

void CActor::InitAfterCreation()
{
	m_Equipment->InitAfterCreation();

	// Update consumption
	const auto& equipment = GetEquipment();
	auto* moduleFuelTank = equipment.GetModule<CModuleFuelTank>();
	ASSERT_OR_EXECUTE(moduleFuelTank, return);

	moduleFuelTank->SetCurrentBaseConsumption(FuelConsumption(20));
}

//////////////////////////////////////////////////////////////////////////

void CActor::Tick()
{
	//CheckActorReset();

	Vector2 oldPos = m_Position;

	// Update member
	m_Equipment->Tick();
	m_Motor->Tick();

	// Make camera focus the player
	UpdateCamera(m_Position - oldPos);

	UpdateUI();
}

//////////////////////////////////////////////////////////////////////////

void CActor::Draw() const
{
	auto& renderManager = CRenderManager::GetMutable();
	renderManager.DrawSpriteWorld(m_Position, TextureName::ACTOR, Alignment::CenterBottom);

	// Money
	//renderManager.DrawText(ScreenPos(CRenderManager::Get().GetScreenWidth() - 400.0f, 0.0f), "Money: " + std::to_string(m_Economy->GetMoney().get()));

	const auto* moduleInstance = m_Equipment->GetModule(ModuleType::FuelTank);
	const auto* moduleFuelTank = static_cast<const CModuleFuelTank*>(moduleInstance);
	ASSERT_OR_EXECUTE(moduleFuelTank, return);
	renderManager.DrawTextUI(ScreenPos(CRenderManager::Get().GetBaseScreenWidth() - 400.0f, 0.0f), "Fuel: " + std::to_string(int(moduleFuelTank->GetFuelPercentage() * 100)) + " %");

	// Thruster sprite
	if (m_Motor->IsThrusterInUse())
	{
		renderManager.DrawSpriteWorld(m_Position, TextureName::ACTOR_THRUSTER, Alignment::CenterTop);
	}
}

//////////////////////////////////////////////////////////////////////////

const hvgs::WorldPos& CActor::GetPosition() const
{
	return m_Position;
}

//////////////////////////////////////////////////////////////////////////

void CActor::SetPosition(const WorldPos& position)
{
	if (m_Position == position)
	{
		return;
	}

	m_Position = position;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CInventory& CActor::GetInventory() const
{
	return *m_Inventory;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CInventory& CActor::GetInventory()
{
	return *m_Inventory;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CActorEconomy& CActor::GetEconomy() const
{
	return *m_Economy;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CActorEconomy& CActor::GetEconomy()
{
	return *m_Economy;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CActorHealth& CActor::GetHealth() const
{
	return *m_Health;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CActorHealth& CActor::GetHealth()
{
	return *m_Health;
}

//////////////////////////////////////////////////////////////////////////

const hvgs::CEquipment& CActor::GetEquipment() const
{
	return *m_Equipment;
}

//////////////////////////////////////////////////////////////////////////

hvgs::CEquipment& CActor::GetEquipment()
{
	return *m_Equipment;
}

//////////////////////////////////////////////////////////////////////////

void CActor::StartDigging(const CTile& tile)
{
	m_Motor = std::make_unique<CMotorDigging>(*m_Motor);
	auto motorDigging = static_cast<CMotorDigging*>(m_Motor.get());
	motorDigging->SetTargetPosition(tile.GetCenter() - WorldPos{ 0.0f, 0.5f });
	motorDigging->SetDiggingPower(0.8f);
}

//////////////////////////////////////////////////////////////////////////

void CActor::StopDigging()
{
	m_Motor = std::make_unique<CMotorDefault>(*m_Motor);
}

//////////////////////////////////////////////////////////////////////////

void CActor::UpdateCamera(const Vector2& deltaMovement) const
{
	// Update camera
	CCamera* cam = CCameraManager::GetMutable().GetActive();
	ASSERT_OR_EXECUTE(cam, return);

	cam->SetPosition(cam->GetPosition() + deltaMovement);
}

//////////////////////////////////////////////////////////////////////////

void CActor::UpdateUI() const
{
	bool interactionButtonPressed = CInputManager::Get().GetButtonDown(Button::ToggleInventory);

	if (interactionButtonPressed)
	{
		bool inputUsed = false;
		for (const auto& interactionObject : CInteractionManager::Get().GetInteractionObjects())
		{
			if (interactionObject->IsInInteractionDistance(m_Position))
			{
				interactionObject->StartInteraction();
				inputUsed = true;
				break;
			}
		}

		if (!inputUsed)
		{
			ui::CSceneManager::GetMutable().ToggleState(ui::SceneID::Inventory);
		}
	}

	bool genericDebugPressed = CInputManager::Get().GetButtonDown(Button::GenericDebug);
	if (genericDebugPressed)
	{
		ui::CSceneManager::GetMutable().ToggleState(ui::SceneID::BuildingWorkshop);
	}
}

//////////////////////////////////////////////////////////////////////////

void CActor::CheckActorReset()
{
	if (CInputManager::Get().IsMouseButtonDown(MouseButton::Middle)
		|| std::abs(m_Position.x) > 200.0f
		|| m_Position.y > 20.0f
		|| m_Position.y <= -100.0f
		|| m_Position.x <= CHUNKSLICE_SIZE_X * -4
		|| m_Position.x >= CHUNKSLICE_SIZE_X * 4)
	{
		UpdateCamera(-m_Position);
		SetPosition(Vector2(0.0f, 0.0f));
		m_Motor->SetVelocity({ 0.0f, 0.0f });
	}
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CActor::GetAABBOrigin() const
{
	return m_Position + GetAABBOriginOffset();
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CActor::GetAABBHalfs() const
{
	return{ 0.43f, 0.38f }; // In world coords
}

//////////////////////////////////////////////////////////////////////////

hvgs::WorldPos CActor::GetAABBOriginOffset() const
{
	return{ 0.0f, GetAABBHalfs().y };
}

//////////////////////////////////////////////////////////////////////////

Layer CActor::GetLayer() const
{
	return Layer::Actor;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
