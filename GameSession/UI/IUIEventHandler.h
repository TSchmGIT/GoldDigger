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
	virtual void OnMousePressed(const ScreenPos&) { }
};

/////////////////////////////////////////////////////////////////////////////

} // hvgs::ui