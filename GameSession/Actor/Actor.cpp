#include "stdafx.h"
#include "Actor.h"

#include <hvmath/Physics/AABB.h>

#include "GameSession/Actor/Economy/ActorEconomy.h"
#include "GameSession/Actor/Motor/MotorDefault.h"
#include "GameSession/Actor/Motor/MotorDigging.h"
#include "GameSession/Camera/Camera.h"
#include "GameSession/Items/Inventory.h"
#include "GameSession/Items/ItemBlock.h"
#include "GameSession/Items/ItemStack.h"
#include "GameSession/Manager/CameraManager.h"
#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/PhysicsManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/TimeManager.h"
#include "GameSession/Physics/PhysicsEnums.h"
#include "GameSession/Rendering/DebugRender.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"
#include "GameSession/UI/Scenes/Meta/SceneEnum.h"
#include "GameSession/UI/Scenes/Meta/SceneManager.h"
#include "GameSession/World/Tile.h"
#include "GameSession/World/World.h"
#include "Manager/InteractionManager.h"
#include "Interaction/IInteractionObject.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{


////////////////////////////////////////////////////////////////////////////

CActor::CActor()
{
}

//////////////////////////////////////////////////////////////////////////

CActor::CActor(const CActor& other)
{
	if (other.m_Inventory)
	{
		m_Inventory = std::make_unique<CInventory>(*other.m_Inventory);
	}
}

//////////////////////////////////////////////////////////////////////////

CActor::CActor(CActor&& other)
	: m_Position(other.m_Position)
	, m_Inventory(std::move(other.m_Inventory))
	, m_Motor(std::move(other.m_Motor))
{

}

//////////////////////////////////////////////////////////////////////////

CActor::~CActor()
{

}

//////////////////////////////////////////////////////////////////////////

void CActor::PrepareTick()
{

}

//////////////////////////////////////////////////////////////////////////

void CActor::Tick()
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

	Vector2 oldPos = m_Position;

	// Update motor
	m_Motor->Tick();

	//// Collect tiles
	//if (CInputManager::Get().IsMouseButtonDown(MouseButton::Left))
	//{
	//	CCamera* cam = CCameraManager::GetMutable().GetActive();
	//	ASSERT_OR_EXECUTE(cam, return);

	//	auto&& tile = CWorld::GetMutable()->GetTileAt(cam->ScreenToWorldPoint(CInputManager::Get().GetMousePos()));

	//	if (tile && tile->GetTileType() != TileType::Air)
	//	{
	//		m_Inventory->AddItem(std::make_unique<CItemBlock>(tile->GetTileType()));

	//		CWorld::GetMutable()->SetTileAt(cam->ScreenToWorldPoint(CInputManager::Get().GetMousePos()), TileType::Air, false);
	//	}
	//}

	//// Place tiles
	//if (CInputManager::Get().IsMouseButtonDown(MouseButton::Right) && m_Inventory->HasItems())
	//{
	//	CCamera* cam = CCameraManager::GetMutable().GetActive();
	//	ASSERT_OR_EXECUTE(cam, return);

	//	auto&& item = m_Inventory->GetStackAt(0)->GetFirstItem();
	//	auto&& itemBlock = dynamic_cast<const CItemBlock*>(item);
	//	if (itemBlock)
	//	{
	//		CWorld::GetMutable()->SetTileAt(cam->ScreenToWorldPoint(CInputManager::Get().GetMousePos()), itemBlock->GetTileType(), false);

	//		m_Inventory->RemoveStackAt(0);
	//	}
	//}

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
	renderManager.DrawText(ScreenPos(CRenderManager::Get().GetScreenWidth() - 400.0f, 0.0f), "Money: " + std::to_string(m_Economy->GetMoney().get()));

	// Thruster sprite
	if (m_Motor->IsThrusterInUse())
	{
		renderManager.DrawSpriteWorld(m_Position, TextureName::ACTOR_THRUSTER, Alignment::CenterTop);
	}

	// Debug
	//std::ostringstream ss;
	//ss << "(" << m_Position.x << ", " << m_Position.y << ")\n" <<
	//	m_Motor->GetVelocity().x << ", " << m_Motor->GetVelocity().y << ")";
	//CRenderManager::GetMutable().DrawTextWorld(m_Position, ss.str(), FontName::Courier_New, 30);
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

void CActor::StartDigging(const CTile& tile)
{
	m_Motor = std::make_unique<CMotorDigging>(*m_Motor);
	CMotorDigging* motorDigging = boost::dynamic_pointer_cast<CMotorDigging>(m_Motor.get());
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
			if (CInputManager::Get().GetButtonDown(Button::ToggleInventory))
			{
				ui::CSceneManager::GetMutable().ToggleState(ui::SceneID::Inventory);
			}
		}
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
