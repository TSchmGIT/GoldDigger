#include "stdafx.h"
#include "IInteractionObject.h"

#include "GameSession/Manager/InteractionManager.h"
#include "../../World/World.h"
#include "../Actor.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/RenderManager.h"
#include "../../Rendering/Textures/EnumsTexture.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

IInteractionObject::IInteractionObject()
{
	CInteractionManager::GetMutable().RegisterInteractionObject(this);
}

//////////////////////////////////////////////////////////////////////////

IInteractionObject::IInteractionObject(const IInteractionObject&)
{
	CInteractionManager::GetMutable().RegisterInteractionObject(this);
}

//////////////////////////////////////////////////////////////////////////

IInteractionObject::IInteractionObject(IInteractionObject&&)
{
	CInteractionManager::GetMutable().RegisterInteractionObject(this);
}

//////////////////////////////////////////////////////////////////////////

IInteractionObject& IInteractionObject::operator=(const IInteractionObject&)
{
	return *this;
}

//////////////////////////////////////////////////////////////////////////

IInteractionObject& IInteractionObject::operator=(IInteractionObject&&)
{
	return *this;
}

//////////////////////////////////////////////////////////////////////////

IInteractionObject::~IInteractionObject()
{
	CInteractionManager::GetMutable().UnregisterInteractionObject(this);
}

//////////////////////////////////////////////////////////////////////////

void IInteractionObject::Tick()
{
	// #TODO @tschmiedel: May interchange the showing of interaction symbols to the actor, because there may be too many things to check

	// Check if the interaction symbol should be shown
	const auto& actor = CWorld::Get().GetActor();

	m_IsInInteractionRange = Vector2::DistanceCheck(actor.GetPosition(), GetInteractionOriginPosition(), m_InteractionDistance);

	bool interactionActive = false;

	if (m_IsInteractionActive)
	{
		interactionActive = m_IsInInteractionRange;
	}
	else
	{
		if (m_IsInInteractionRange)
		{
			Button toggleUIButton = Button::ToggleInventory;
			interactionActive = CInputManager::Get().GetButtonDown(toggleUIButton);

			if (interactionActive)
			{
				CInputManager::GetMutable().SetButtonUsed(toggleUIButton);
				StartInteraction();
			}
		}
	}

	// Do nothing if interaction state has not changed
	if (m_IsInteractionActive == interactionActive)
	{
		return;
	}
	m_IsInteractionActive = interactionActive;

	// React on interaction change state
	if (interactionActive) //< interaction has begun
	{
		StartInteraction();
	}
	else
	{
		StopInteraction();
	}
}

//////////////////////////////////////////////////////////////////////////

void IInteractionObject::Draw() const
{
	if (m_IsInInteractionRange)
	{
		if (m_IsInteractionActive)
		{

		}
		else
		{
			// Show interaction buttons
			CRenderManager::GetMutable().DrawSpriteWorld(GetInteractionButtonPosition(), TextureName::BUTTON_SPECIAL_INTERACTION, 1.0f, Alignment::CenterBottom);
		}
	}
	else
	{

	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
