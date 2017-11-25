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
	for (int i = 0; i < int(JoystickID::Count); i++)
	{
		JoystickID joystickId = JoystickID(i);
		auto itPairUp = m_JoystickButtonMapUp.emplace(joystickId, new bool[size_t(JoystickButton::Count)]);
		auto itPairDown = m_JoystickButtonMapDown.emplace(joystickId, new bool[size_t(JoystickButton::Count)]);
		auto itPairPressed = m_JoystickButtonMapPressed.emplace(joystickId, new bool[size_t(JoystickButton::Count)]);

		for (hvint8 j = 0; j < hvint8(JoystickButton::Count); j++)
		{
			itPairUp.first->second[j] = false;
			itPairDown.first->second[j] = false;
			itPairPressed.first->second[j] = false;
		}

		Map<JoystickAxis, float> mapAxis;
		for (int j = 0; j < int(JoystickAxis::Count); j++)
		{
			mapAxis.emplace(JoystickAxis(j), 0.0f);
		}

		m_JoystickAxis.emplace(JoystickID(i), std::move(mapAxis));
	}
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::PrepareTick()
{
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

	m_SignalMouseClicked(m_MousePos);
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

	m_SignalMouseMove(m_MouseDelta, m_MousePos);
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

const Vector2i& CInputManager::GetMousePos() const
{
	return m_MousePos;
}

//////////////////////////////////////////////////////////////////////////

const Vector2i& CInputManager::GetMouseDelta() const
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

float CInputManager::GetAxis(Axis axis, JoystickID id /*= JoystickID::Player1*/) const
{
	KeyCode keyNeg = KeyCode::Unknown;
	KeyCode keyPos = KeyCode::Unknown;

	JoystickAxis joystickAxis = JoystickAxis::Unknown;
	JoystickAxis joystickAxisAlt = JoystickAxis::Unknown;

	switch (axis)
	{
	case hvgs::Axis::Horizontal:
		keyNeg = KeyCode::A;
		keyPos = KeyCode::D;

		joystickAxis = JoystickAxis::LeftX;
		joystickAxisAlt = JoystickAxis::PadX;
		break;
	case hvgs::Axis::Vertical:
		keyNeg = KeyCode::S;
		keyPos = KeyCode::W;

		joystickAxis = JoystickAxis::LeftY;
		joystickAxisAlt = JoystickAxis::PadY;
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

	return hvmath::Clamp(result + GetJoystickAxis(joystickAxis, id) + GetJoystickAxis(joystickAxisAlt, id), -1.0f, 1.0f);
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::GetButton(Button button, JoystickID id /*= JoystickID::Player1*/) const
{
	auto[keyButton, joystickButton] = GetDataForButton(button);

	return IsKeyPressed(keyButton) || IsJoystickButtonPressed(joystickButton, id);
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::GetButtonDown(Button button, JoystickID id /*= JoystickID::Player1*/) const
{
	auto[keyButton, joystickButton] = GetDataForButton(button);

	return IsKeyDown(keyButton) || IsJoystickButtonDown(joystickButton, id);
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::GetButtonUp(Button button, JoystickID id /*= JoystickID::Player1*/) const
{
	auto[keyButton, joystickButton] = GetDataForButton(button);

	return IsKeyPressed(keyButton) || IsJoystickButtonPressed(joystickButton, id);
}

//////////////////////////////////////////////////////////////////////////

std::tuple<hvgs::KeyCode, hvgs::JoystickButton> CInputManager::GetDataForButton(Button button) const
{
	switch (button)
	{
	case hvgs::Button::Jump:
		return{ KeyCode::Space, JoystickButton::XBOX_A };
	case hvgs::Button::Dig:
		return{ KeyCode::LShift, JoystickButton::XBOX_B };
	default:
		return{ KeyCode::Unknown, JoystickButton::Unknown };
	}

}

//////////////////////////////////////////////////////////////////////////

void CInputManager::UpdateJoystickAxisPosition(JoystickID id, JoystickAxis axis, float position)
{
	if (axis == JoystickAxis::LeftY)
	{
		position = -position;
	}

	auto itID = m_JoystickAxis.find(id);
	ASSERT_OR_EXECUTE(itID != m_JoystickAxis.end(), return);
	auto itAxis = itID->second.find(axis);
	ASSERT_OR_EXECUTE(itAxis != itID->second.end(), return);

	itAxis->second = hvmath::Deadzone(position * 0.01f, 0.25f); // The sfml value is between -100.0f and 100.0f
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::RegisterJoystickButtonPressed(JoystickID id, JoystickButton button)
{
	auto itDownID = m_JoystickButtonMapDown.find(id);
	auto itUpID = m_JoystickButtonMapUp.find(id);
	auto itPressedID = m_JoystickButtonMapPressed.find(id);
	ASSERT_OR_EXECUTE(itDownID != m_JoystickButtonMapDown.end() && itUpID != m_JoystickButtonMapUp.end() && itPressedID != m_JoystickButtonMapPressed.end(), return);

	bool* downArray = itDownID->second;
	bool* upArray = itUpID->second;
	bool* pressedArray = itPressedID->second;
	ASSERT_OR_EXECUTE(downArray && upArray && pressedArray, return);


	// When the button was released it cannot be pressed down
	upArray[size_t(button)] = false;

	downArray[size_t(button)] = !pressedArray[size_t(button)];

	// Update pressed Array
	pressedArray[size_t(button)] = true;
}

//////////////////////////////////////////////////////////////////////////

void CInputManager::RegisterJoystickButtonReleased(JoystickID id, JoystickButton button)
{
	auto itDownID = m_JoystickButtonMapDown.find(id);
	auto itUpID = m_JoystickButtonMapUp.find(id);
	auto itPressedID = m_JoystickButtonMapPressed.find(id);
	ASSERT_OR_EXECUTE(itDownID != m_JoystickButtonMapDown.end() && itUpID != m_JoystickButtonMapUp.end() && itPressedID != m_JoystickButtonMapPressed.end(), return);

	bool* downArray = itDownID->second;
	bool* upArray = itUpID->second;
	bool* pressedArray = itPressedID->second;
	ASSERT_OR_EXECUTE(downArray && upArray && pressedArray, return);

	// When the button was released it cannot be pressed down
	downArray[size_t(button)] = false;

	upArray[size_t(button)] = pressedArray[size_t(button)];

	// Update pressed Array
	pressedArray[size_t(button)] = false;
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsJoystickButtonDown(JoystickButton button, JoystickID id /*= JoystickID::Player1*/) const
{
	ASSERT_OR_EXECUTE(button != JoystickButton::Unknown && button < JoystickButton::Count, return false);
	auto it = m_JoystickButtonMapDown.find(id);
	ASSERT_OR_EXECUTE(it != m_JoystickButtonMapDown.end(), return false);
	return it->second[size_t(button)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsJoystickButtonUp(JoystickButton button, JoystickID id /*= JoystickID::Player1*/) const
{
	ASSERT_OR_EXECUTE(button != JoystickButton::Unknown && button < JoystickButton::Count, return false);
	auto it = m_JoystickButtonMapUp.find(id);
	ASSERT_OR_EXECUTE(it != m_JoystickButtonMapUp.end(), return false);
	return it->second[size_t(button)];
}

//////////////////////////////////////////////////////////////////////////

bool CInputManager::IsJoystickButtonPressed(JoystickButton button, JoystickID id /*= JoystickID::Player1*/) const
{
	ASSERT_OR_EXECUTE(button != JoystickButton::Unknown && button < JoystickButton::Count, return false);
	auto it = m_JoystickButtonMapPressed.find(id);
	ASSERT_OR_EXECUTE(it != m_JoystickButtonMapPressed.end(), return false);
	return it->second[size_t(button)];
}

//////////////////////////////////////////////////////////////////////////

float CInputManager::GetJoystickAxis(JoystickAxis axis, JoystickID id /*= JoystickID::Player1*/) const
{
	auto itId = m_JoystickAxis.find(id);
	if (itId == m_JoystickAxis.end())
	{
		return 0.0f;
	}

	auto itAxis = itId->second.find(axis);
	ASSERT_OR_EXECUTE(itAxis != itId->second.end(), return 0.0f);
	return itAxis->second;
}

//////////////////////////////////////////////////////////////////////////

} // hvgs
