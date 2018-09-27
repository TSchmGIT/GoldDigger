#include "stdafx.h"
#include "IUIEventHandler.h"

#include "GameSession\Manager\InputManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

IUIEventHandler::IUIEventHandler()
{
	SetupConnections();
}

//////////////////////////////////////////////////////////////////////////

IUIEventHandler::IUIEventHandler(const IUIEventHandler&)
{
	SetupConnections();
}

//////////////////////////////////////////////////////////////////////////

IUIEventHandler::~IUIEventHandler()
{
	m_MouseClickedConnection.disconnect();
	m_MouseMoveConnection.disconnect();
	m_MouseDownConnection.disconnect();
	m_MouseUpConnection.disconnect();
}

//////////////////////////////////////////////////////////////////////////

void IUIEventHandler::SetupConnections()
{
	m_MouseClickedConnection = CInputManager::GetMutable().ConnectSignal<SignalMouseClickedConnector>(SignalMouseClickedConnector(boost::bind(&IUIEventHandler::OnMouseClicked, this, _1)));
	m_MouseMoveConnection = CInputManager::GetMutable().ConnectSignal<SignalMouseMoveConnector>(SignalMouseMoveConnector(boost::bind(&IUIEventHandler::OnMouseMove, this, _1, _2)));
	m_MouseDownConnection = CInputManager::GetMutable().ConnectSignal<SignalMouseDownConnector>(SignalMouseDownConnector(boost::bind(&IUIEventHandler::OnMouseDown, this, _1)));
	m_MouseUpConnection = CInputManager::GetMutable().ConnectSignal<SignalMouseUpConnector>(SignalMouseUpConnector(boost::bind(&IUIEventHandler::OnMouseUp, this, _1)));
}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
