#include "stdafx.h"
#include "GameManager.h"

#include <SFML/Window/Event.hpp>

#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/RenderManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CGameManager::CGameManager()
{

}

//////////////////////////////////////////////////////////////////////////

CGameManager::~CGameManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Init()
{
	//////////////////////////////////////////////////////////////////////////
	// Render
	//////////////////////////////////////////////////////////////////////////
	CRenderManager::GetMutable().Init();

	//////////////////////////////////////////////////////////////////////////
	// Input
	//////////////////////////////////////////////////////////////////////////
	CInputManager::GetMutable().Init();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Shutdown()
{

}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Run()
{
	while (CRenderManager::Get().GetWindow()->isOpen())
	{
		PrepareTick();

		PollEvents();

		if (CInputManager::Get().IsMouseButtonDown(MouseButton::Left))
		{
			LOG_INFO("LMB down");
		}
		if (CInputManager::Get().IsMouseButtonUp(MouseButton::Left))
		{
			LOG_INFO("LMB up");
		}

		if (CInputManager::Get().IsMouseButtonDown(MouseButton::Right))
		{
			LOG_INFO("RMB down");
		}
		if (CInputManager::Get().IsMouseButtonUp(MouseButton::Right))
		{
			LOG_INFO("RMB up");
		}

		CRenderManager::GetMutable().GetWindow()->clear();
		CRenderManager::GetMutable().GetWindow()->display();
	}
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::PrepareTick()
{
	CInputManager::GetMutable().ResetIntermediateStatus();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::PollEvents()
{
	sf::Event pollEvent;
	while (CRenderManager::GetMutable().GetWindow()->pollEvent(pollEvent))
	{
		switch (pollEvent.type)
		{
		case sf::Event::EventType::KeyPressed:
			CInputManager::GetMutable().RegisterKeyPressed(KeyCode(pollEvent.key.code));
			break;
		case sf::Event::EventType::KeyReleased:
			CInputManager::GetMutable().RegisterKeyReleased(KeyCode(pollEvent.key.code));
			break;
		case sf::Event::EventType::MouseButtonPressed:
			CInputManager::GetMutable().RegisterMouseButtonPressed(MouseButton(pollEvent.mouseButton.button));
			break;
		case sf::Event::EventType::MouseButtonReleased:
			CInputManager::GetMutable().RegisterMouseButtonReleased(MouseButton(pollEvent.mouseButton.button));
			break;
		default:
			break;
		}

		if (pollEvent.type == sf::Event::Closed)
			CRenderManager::GetMutable().GetWindow()->close();
	}
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
