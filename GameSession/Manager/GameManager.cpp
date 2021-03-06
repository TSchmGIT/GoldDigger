#include "stdafx.h"
#include "GameManager.h"

#include <SFML/Window/Event.hpp>

#include "GameSession/Actor/Actor.h"
#include "GameSession/Manager/CameraManager.h"
#include "GameSession/Manager/GameObjectManager.h"
#include "GameSession/Manager/InputManager.h"
#include "GameSession/Manager/RenderManager.h"
#include "GameSession/Manager/TimeManager.h"
#include "GameSession/Rendering/Textures/EnumsTexture.h"

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
	CTimeManager::GetMutable().Init();

	//////////////////////////////////////////////////////////////////////////
	// Render
	//////////////////////////////////////////////////////////////////////////
	CRenderManager::GetMutable().Init();
	CCameraManager::GetMutable().Init();

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

		Tick();

		Render();
	}
	std::cout << "Time passed upon end from game clock: " << CTimeManager::Get().GetAppTime() << " seconds";
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::PrepareTick()
{
	CRenderManager::GetMutable().PrepareTick();
	CTimeManager::GetMutable().PrepareTick();
	CInputManager::GetMutable().PrepareTick();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::PollEvents()
{
	sf::Event pollEvent;
	while (CRenderManager::GetMutable().GetWindow()->pollEvent(pollEvent))
	{
		switch (pollEvent.type)
		{
			//////////////////////////////////////////////////////////////////////////
			// Input
			//////////////////////////////////////////////////////////////////////////
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
		case sf::Event::EventType::MouseMoved:
			CInputManager::GetMutable().UpdateMouseCursorPosition(pollEvent.mouseMove.x, pollEvent.mouseMove.y);
			break;
		case sf::Event::EventType::MouseWheelScrolled:
			CInputManager::GetMutable().UpdateMouseWheelDelta(pollEvent.mouseWheelScroll.delta);
			break;
		case sf::Event::EventType::JoystickMoved:
			CInputManager::GetMutable().UpdateJoystickAxisPosition(JoystickID(pollEvent.joystickMove.joystickId), JoystickAxis(pollEvent.joystickMove.axis), pollEvent.joystickMove.position);
			break;
		case sf::Event::EventType::JoystickButtonPressed:
			CInputManager::GetMutable().RegisterJoystickButtonPressed(JoystickID(pollEvent.joystickButton.joystickId), JoystickButton(pollEvent.joystickButton.button));
			break;
		case sf::Event::EventType::JoystickButtonReleased:
			CInputManager::GetMutable().RegisterJoystickButtonReleased(JoystickID(pollEvent.joystickButton.joystickId), JoystickButton(pollEvent.joystickButton.button));
			break;
		case sf::Event::EventType::Closed:
			CRenderManager::GetMutable().GetWindow()->close();
			break;
		default:
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Tick()
{
	CCameraManager::GetMutable().Tick();
	CGameObjectManager::GetMutable().Tick();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Render()
{
	CRenderManager::GetMutable().Render();

	Draw();

	CRenderManager::GetMutable().Display();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Draw() const
{
	static float timestamp = 0.0f;
	static float lastFPS = 0.0f;

	if (timestamp + 0.25f < CTimeManager::Get().GetAppTime())
	{
		lastFPS = CTimeManager::Get().GetFPS();
		timestamp = CTimeManager::Get().GetAppTime();
	}
	std::ostringstream ss;
	ss << "FPS: " << lastFPS;
	CRenderManager::GetMutable().DrawText(ScreenPos(0.0f, 0.0f), ss.str(), FontName::Courier_New);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
