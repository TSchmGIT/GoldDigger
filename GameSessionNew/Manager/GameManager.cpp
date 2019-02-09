#include "stdafx.h"
#include "GameManager.h"

#include <SFML/Window/Event.hpp>

#include "GameSessionNew/Actor/Actor.h"
#include "GameSessionNew/Data/DataModuleManager.h"
#include "GameSessionNew/Manager/CameraManager.h"
#include "GameSessionNew/Manager/GameObjectManager.h"
#include "GameSessionNew/Manager/InputManager.h"
#include "GameSessionNew/Manager/InteractionManager.h"
#include "GameSessionNew/Manager/RenderManager.h"
#include "GameSessionNew/Manager/TimeManager.h"
#include "GameSessionNew/Manager/UIManager.h"
#include "GameSessionNew/Rendering/Textures/EnumsTexture.h"
#include "GameSessionNew/UI/Scenes/Meta/SceneManager.h"
#include "GameSessionNew/World/World.h"

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

void CGameManager::Construct()
{
	Init();

	InitAfterCreation();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Init()
{
	hvda::CDataModuleManager::GetMutable().Init();

	//////////////////////////////////////////////////////////////////////////

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

	//////////////////////////////////////////////////////////////////////////
	// UI
	//////////////////////////////////////////////////////////////////////////
	ui::CSceneManager::GetMutable().Init();

	//////////////////////////////////////////////////////////////////////////
	// Other
	//////////////////////////////////////////////////////////////////////////
	m_World->Init();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::InitAfterCreation()
{
	CGameObjectManager::GetMutable().InitAfterCreation();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Shutdown()
{
	m_World->Shutdown();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Run()
{
	while (CRenderManager::Get().GetWindow().isOpen())
	{
		PrepareTick();

		PollEvents();

		Tick();

		Render();
	}
	std::cout << "Time passed upon end from game clock: " << CTimeManager::Get().GetAppTime() << " seconds";
}

//////////////////////////////////////////////////////////////////////////

hvgs::CWorld& CGameManager::GetWorld() const
{
	return *m_World;
}

//////////////////////////////////////////////////////////////////////////

String CGameManager::GetWorkingDir()
{
	static std::array<char, 256> buffer;
	GetCurrentDirectoryA(buffer.size(), buffer.data());
	return String(buffer.data());
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::PrepareTick()
{
	CRenderManager::GetMutable().PrepareTick();
	CTimeManager::GetMutable().PrepareTick();
	CInputManager::GetMutable().PrepareTick();
	CGameObjectManager::GetMutable().PrepareTick();
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::PollEvents()
{
	sf::Event pollEvent;
	while (CRenderManager::GetMutable().PollEvent(pollEvent))
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
		case sf::Event::EventType::Resized:
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0.0f, 0.0f, float(pollEvent.size.width), float(pollEvent.size.height));
			CRenderManager::GetMutable().SetView(sf::View(visibleArea));
			break;
		}
		case sf::Event::EventType::Closed:
			CRenderManager::GetMutable().CloseWindow();
			break;
		default:
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CGameManager::Tick()
{
	m_World->Tick();

	CCameraManager::GetMutable().Tick();
	CGameObjectManager::GetMutable().Tick();
	CInteractionManager::GetMutable().Tick();

	hvgs::ui::CSceneManager::GetMutable().SyncTick();
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
		lastFPS = CTimeManager::Get().GetFPSAverage();
		timestamp = CTimeManager::Get().GetAppTime();
	}

	std::ostringstream ss;
	ss.precision(3);
	ss << "FPS: " << lastFPS;
	CRenderManager::GetMutable().DrawTextUI(ScreenPos(0.0f, 0.0f), ss.str(), Alignment::TopLeft, FontName::Courier_New);
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
