#pragma once
#include "GameSession/Input/InputEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

class CInputManager : public CSingletonBase<CInputManager>
{

public:
	CInputManager();
	virtual ~CInputManager();

	void Init();

public:
	void PrepareTick();

	//////////////////////////////////////////////////////////////////////////
	// Keyboard
	//////////////////////////////////////////////////////////////////////////
	void RegisterKeyPressed(KeyCode keycode);
	void RegisterKeyReleased(KeyCode keycode);

public:
	bool IsKeyPressed(KeyCode keyCode) const;
	bool IsKeyDown(KeyCode keyCode) const;
	bool IsKeyUp(KeyCode keyCode) const;


	//////////////////////////////////////////////////////////////////////////
	// Mouse
	//////////////////////////////////////////////////////////////////////////
	void RegisterMouseButtonPressed(MouseButton button);
	void RegisterMouseButtonReleased(MouseButton button);

	void UpdateMouseCursorPosition(int x, int y);
	void UpdateMouseWheelDelta(float delta);

public:
	bool IsMouseButtonPressed(MouseButton button) const;
	bool IsMouseButtonUp(MouseButton button) const;
	bool IsMouseButtonDown(MouseButton button) const;

	const Vector2i& GetMousePos() const;
	const Vector2i& GetMouseDelta() const;

	float		GetMouseWheelDelta() const;
	float		GetMouseWheelPos() const;

	//////////////////////////////////////////////////////////////////////////
	/// Joystick
	//////////////////////////////////////////////////////////////////////////
	void UpdateJoystickAxisPosition(JoystickID id, JoystickAxis axis, float position);

	void RegisterJoystickButtonPressed(JoystickID id, JoystickButton button);
	void RegisterJoystickButtonReleased(JoystickID id, JoystickButton button);

public:
	bool IsJoystickButtonDown(JoystickButton button, JoystickID id = JoystickID::Player1) const;
	bool IsJoystickButtonUp(JoystickButton button, JoystickID id = JoystickID::Player1) const;
	bool IsJoystickButtonPressed(JoystickButton button, JoystickID id = JoystickID::Player1) const;

	float GetJoystickAxis(JoystickAxis axis, JoystickID id = JoystickID::Player1) const;

public:
	float GetAxis(Axis axis, JoystickID id = JoystickID::Player1) const;
	bool GetButton(Button button, JoystickID id = JoystickID::Player1) const;
	bool GetButtonDown(Button button, JoystickID id = JoystickID::Player1) const;
	bool GetButtonUp(Button button, JoystickID id = JoystickID::Player1) const;

	//////////////////////////////////////////////////////////////////////////
	// Signals
	//////////////////////////////////////////////////////////////////////////
public:
	template<typename T>
	constexpr void ConnectSignal(T function);

protected:
	std::tuple<KeyCode, JoystickButton> GetDataForButton(Button button) const;

	bool m_KeyCodeArrayPressed[size_t(KeyCode::Count)];
	bool m_KeyCodeArrayDown[size_t(KeyCode::Count)];
	bool m_KeyCodeArrayUp[size_t(KeyCode::Count)];

	bool m_MouseButtonArrayPressed[size_t(MouseButton::Count)];
	bool m_MouseButtonArrayDown[size_t(MouseButton::Count)];
	bool m_MouseButtonArrayUp[size_t(MouseButton::Count)];

	Map<JoystickID, bool*> m_JoystickButtonMapPressed;
	Map<JoystickID, bool*> m_JoystickButtonMapDown;
	Map<JoystickID, bool*> m_JoystickButtonMapUp;

	Map<JoystickID, Map<JoystickAxis, float>> m_JoystickAxis;

	Vector2i	m_MousePos;
	Vector2i	m_MouseDelta;
	float		m_MouseWheelDelta;
	float		m_MouseWheelPos;

	SignalMouseMove		m_SignalMouseMove;
	SignalMouseClicked	m_SignalMouseClicked;
	SignalMouseDown		m_SignalMouseDown;
};

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr void hvgs::CInputManager::ConnectSignal(T function)
{
	if constexpr (std::is_same<T, SignalMouseMoveConnector>::value)
	{
		m_SignalMouseMove.connect(function);
	}
	else if constexpr (std::is_same<T, SignalMouseClickedConnector>::value)
	{
		m_SignalMouseClicked.connect(function);
	}
	else if constexpr (std::is_same<T, SignalMouseDownConnector>::value)
	{
		m_SignalMouseDown.connect(function);
	}
	else
	{
		WRONG_CONNECTOR_TYPE;
	}
}

/////////////////////////////////////////////////////////////////////////////

} // hvgs
