#include "stdafx.h"
#include "IUIEventHandler.h"

#include "GameSession\Manager\InputManager.h"

//////////////////////////////////////////////////////////////////////////

namespace hvgs::ui
{

//////////////////////////////////////////////////////////////////////////

IUIEventHandler::IUIEventHandler()
{
	CInputManager::GetMutable().ConnectSignal<SignalMouseClickedConnector>(boost::bind(&IUIEventHandler::OnMouseClicked, this, _1));
	CInputManager::GetMutable().ConnectSignal<SignalMouseMoveConnector>(boost::bind(&IUIEventHandler::OnMouseMove, this, _1, _2));
}

//////////////////////////////////////////////////////////////////////////

IUIEventHandler::~IUIEventHandler()
{

}

//////////////////////////////////////////////////////////////////////////

} // hvgs::ui
