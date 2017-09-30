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
	void ResetIntermediateStatus();
	void RegisterKeyPressed(KeyCode keycode);
	void RegisterKeyReleased(KeyCode keycode);

	void RegisterMouseButtonPressed(MouseButton button);
	void RegisterMouseButtonReleased(MouseButton button);

public:
	bool IsKeyPressed(KeyCode keyCode) const;
	bool IsKeyDown(KeyCode keyCode) const;
	bool IsKeyUp(KeyCode keyCode) const;

public:
	bool IsMouseButtonPressed(MouseButton button) const;
	bool IsMouseButtonUp(MouseButton button) const;
	bool IsMouseButtonDown(MouseButton button) const;	

public:
	float GetAxis(Axis axis) const;

protected:
	bool m_KeyCodeArrayPressed[size_t(KeyCode::Count)];
	bool m_KeyCodeArrayDown[size_t(KeyCode::Count)];
	bool m_KeyCodeArrayUp[size_t(KeyCode::Count)];

	bool m_MouseButtonArrayPressed[size_t(MouseButton::Count)];
	bool m_MouseButtonArrayDown[size_t(MouseButton::Count)];
	bool m_MouseButtonArrayUp[size_t(MouseButton::Count)];

};

/////////////////////////////////////////////////////////////////////////////

} // hvgs
