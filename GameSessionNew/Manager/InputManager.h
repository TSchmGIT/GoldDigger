#pragma once
#include "GameSessionNew/Input/InputEnums.h"

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////

using KeyCodeArray = std::array<bool, size_t(KeyCode::Count)>;
using MouseButtonArray = std::array<bool, size_t(MouseButton::Count)>;
using ButtonArray = std::array<bool, size_t(Button::Count)>;
using JoystickButtonArray = std::array<bool, size_t(JoystickButton::Count)>;
using JoystickAxisArray = std::array<float, size_t(JoystickAxis::Count)>;

template<typename T>
using JoystickIDArray = std::array<T, size_t(JoystickID::Count)>;


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

	bool GetButtonUsed(Button button, JoystickID id = JoystickID::Player1) const;
	void SetButtonUsed(Button button, JoystickID id = JoystickID::Player1);

	//////////////////////////////////////////////////////////////////////////
	// Signals
	//////////////////////////////////////////////////////////////////////////
public:
	template<typename T>
	constexpr SignalConnection ConnectSignal(T function);

protected:
	std::tuple<KeyCode, JoystickButton> GetDataForButton(Button button) const;

	JoystickIDArray<ButtonArray>	m_ButtonUsedArray; ///< Array that indicated whehter a button was used during this frame

	KeyCodeArray		m_KeyCodeArrayPressed;
	KeyCodeArray		m_KeyCodeArrayDown;
	KeyCodeArray		m_KeyCodeArrayUp;

	MouseButtonArray	m_MouseButtonArrayPressed;
	MouseButtonArray	m_MouseButtonArrayDown;
	MouseButtonArray	m_MouseButtonArrayUp;

	JoystickIDArray<JoystickButtonArray>	m_JoystickButtonArrayPressed;
	JoystickIDArray<JoystickButtonArray>	m_JoystickButtonArrayDown;
	JoystickIDArray<JoystickButtonArray>	m_JoystickButtonArrayUp;

	JoystickIDArray<JoystickAxisArray>	m_JoystickAxis;

	Vector2i	m_MousePos;
	Vector2i	m_MouseDelta;
	float		m_MouseWheelDelta;
	float		m_MouseWheelPos;

	SignalMouseMove		m_SignalMouseMove;
	SignalMouseClicked	m_SignalMouseClicked;
	SignalMouseDown		m_SignalMouseDown;
	SignalMouseUp		m_SignalMouseUp;
};

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr SignalConnection hvgs::CInputManager::ConnectSignal(T function)
{
	if constexpr (std::is_same_v<T, SignalMouseMoveConnector>)
	{
		return m_SignalMouseMove.get().connect(function.get());
	}
	else if constexpr (std::is_same_v<T, SignalMouseClickedConnector>)
	{
		return m_SignalMouseClicked.get().connect(function.get());
	}
	else if constexpr (std::is_same_v<T, SignalMouseDownConnector>)
	{
		return m_SignalMouseDown.get().connect(function.get());
	}
	else if constexpr (std::is_same_v<T, SignalMouseUpConnector>)
	{
		return m_SignalMouseUp.get().connect(function.get());
	}
	else
	{
		WRONG_CONNECTOR_TYPE;
	}
}

/////////////////////////////////////////////////////////////////////////////

} // hvgs
