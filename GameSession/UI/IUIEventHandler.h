#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

/////////////////////////////////////////////////////////////////////////////

class IUIEventHandler
{

public:
	IUIEventHandler();
	virtual ~IUIEventHandler();

protected:
	virtual void OnMouseMove(const ScreenPos&, const ScreenPos&) { }
	virtual void OnMouseClicked(const ScreenPos&) { }
	virtual void OnMouseDown(const ScreenPos&) { }
	virtual void OnMouseUp(const ScreenPos&) { }

private:
	SignalConnection m_MouseMoveConnection;
	SignalConnection m_MouseClickedConnection;
	SignalConnection m_MouseDownConnection;
	SignalConnection m_MouseUpConnection;
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui
