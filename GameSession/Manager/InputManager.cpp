#include "stdafx.h"
#include "InputManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

CInputManager::CInputManager()
{
}

//////////////////////////////////////////////////////////////////////////

CInputManager::~CInputManager()
{

}

//////////////////////////////////////////////////////////////////////////

void CInputManager::Init()
{
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::PrepareTick()
{
	//TT_BEGIN("ResetInput");
	for (int i = 0; i < int(KeyCode::Count); i++)
	{
		m_KeyCodeArrayDown[i] = false;
		m_KeyCodeArrayUp[i] = false;
	}

	for (int i = 0; i < int(MouseButton::Count); i++)
	{
		m_MouseButtonArrayDown[i] = false;
		m_MouseButtonArrayUp[i] = false;
	}

	m_MouseWheelDelta = 0.0f;
	//TT_END("ResetInput");
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::RegisterKeyPressed(KeyCode keycode)
{
	// When the key is pressed it cannot be released
	m_KeyCodeArrayUp[size_t(keycode)] = false;

	// Key is only pressed down when it was not pressed before
	m_KeyCodeArrayDown[size_t(keycode)] = !m_KeyCodeArrayPressed[size_t(keycode)];

	// Update pressed Array
	m_KeyCodeArrayPressed[size_t(keycode)] = true;
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::RegisterKeyReleased(KeyCode keycode)
{
	// When the key was released it cannot be pressed down
	m_KeyCodeArrayDown[size_t(keycode)] = false;

	// 
	m_KeyCodeArrayUp[size_t(keycode)] = m_KeyCodeArrayPressed[size_t(keycode)];

	// Update pressed Array
	m_KeyCodeArrayPressed[size_t(keycode)] = false;
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::RegisterMouseButtonPressed(MouseButton button)
{
	// When the key is pressed it cannot be released
	m_MouseButtonArrayUp[size_t(button)] = false;

	// Key is only pressed down when it was not pressed before
	m_MouseButtonArrayDown[size_t(button)] = !m_MouseButtonArrayPressed[size_t(button)];

	// Update pressed Array
	m_MouseButtonArrayPressed[size_t(button)] = true;
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::RegisterMouseButtonReleased(MouseButton button)
{
	// When the key was released it cannot be pressed down
	m_MouseButtonArrayDown[size_t(button)] = false;

	m_MouseButtonArrayUp[size_t(button)] = m_MouseButtonArrayPressed[size_t(button)];

	// Update pressed Array
	m_MouseButtonArrayPressed[size_t(button)] = false;
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::UpdateMouseCursorPosition(int x, int y)
{
	// Set delta
	m_MouseDelta.x = x - m_MousePos.x;
	m_MouseDelta.y = y - m_MousePos.y;

	// Set position
	m_MousePos.x = x;
	m_MousePos.y = y;

	LOG_INFO("Mouse pos: x: " << m_MousePos.x << ", y: " << m_MousePos.y);
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::UpdateMouseWheelDelta(float delta)
{
	m_MouseWheelDelta = delta;
	m_MouseWheelPos += delta;
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsKeyPressed(KeyCode keycode) const
{
	ASSERT_OR_EXECUTE(keycode > KeyCode::Unknown && keycode < KeyCode::Count, return false);
	return m_KeyCodeArrayPressed[size_t(keycode)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsKeyDown(KeyCode keycode) const
{
	ASSERT_OR_EXECUTE(keycode > KeyCode::Unknown && keycode < KeyCode::Count, return false);
	return m_KeyCodeArrayDown[size_t(keycode)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsKeyUp(KeyCode keycode) const
{
	ASSERT_OR_EXECUTE(keycode > KeyCode::Unknown && keycode < KeyCode::Count, return false);
	return m_KeyCodeArrayUp[size_t(keycode)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsMouseButtonPressed(MouseButton button) const
{
	ASSERT_OR_EXECUTE(button >= MouseButton(0) && button < MouseButton::Count, return false);
	return m_MouseButtonArrayPressed[size_t(button)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsMouseButtonUp(MouseButton button) const
{
	ASSERT_OR_EXECUTE(button >= MouseButton(0) && button < MouseButton::Count, return false);
	return m_MouseButtonArrayUp[size_t(button)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsMouseButtonDown(MouseButton button) const
{
	ASSERT_OR_EXECUTE(button >= MouseButton(0) && button < MouseButton::Count, return false);
	return m_MouseButtonArrayDown[size_t(button)];
}

//////////////////////////////////////////////////////////////////////////

Vector2i CInputManager::GetMousePos() const
{
	return m_MousePos;
}

//////////////////////////////////////////////////////////////////////////

Vector2i CInputManager::GetMouseDelta() const
{
	return m_MouseDelta;
}

//////////////////////////////////////////////////////////////////////////

float CInputManager::GetMouseWheelDelta() const
{
	return m_MouseWheelDelta;
}

//////////////////////////////////////////////////////////////////////////

float CInputManager::GetMouseWheelPos() const
{
	return m_MouseWheelPos;
}

//////////////////////////////////////////////////////////////////////////

float CInputManager::GetAxis(Axis axis) const
{
	KeyCode keyNeg = KeyCode::Unknown;
	KeyCode keyPos = KeyCode::Unknown;

	switch (axis)
	{
	case hvgs::Axis::Horizontal:
		keyNeg = KeyCode::A;
		keyPos = KeyCode::D;
		break;
	case hvgs::Axis::Vertical:
		keyNeg = KeyCode::S;
		keyPos = KeyCode::W;
		break;
	default:
		ASSERT_TEXT(false, "Axis is not configured");
		break;
	}

	float result = 0.0f;
	if (IsKeyPressed(keyNeg))
	{
		result -= 1.0f;
	}
	if (IsKeyPressed(keyPos))
	{
		result += 1.0f;
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
