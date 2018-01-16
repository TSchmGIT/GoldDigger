#pragma once

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

enum class EventType
{
	MouseMove,
	MouseClicked,
	MouseDown,
	MouseUp
};


template<typename T>
using Signal = boost::signals2::signal<T>;
using SignalConnection = boost::signals2::connection;

using SignalMouseMove = hvsdk::CNamedType<Signal<void(const ScreenPos&, const ScreenPos&)>, struct SIGNAL_MOUSE_MOVE>;
using SignalMouseMoveConnector = hvsdk::CNamedType<std::function<void(const ScreenPos&, const ScreenPos&)>, struct SIGNAL_MOUSE_MOVE_CONNECTOR>;

using SignalMouseClicked = hvsdk::CNamedType<Signal<void(const ScreenPos&)>, struct SIGNAL_MOUSE_CLICKED>;
using SignalMouseClickedConnector = hvsdk::CNamedType<std::function<void(const ScreenPos&)>, struct SIGNAL_MOUSE_CLICKED_CONNECTOR>;

using SignalMouseDown = hvsdk::CNamedType<Signal<void(const ScreenPos&)>, struct SIGNAL_MOUSE_DOWN>;
using SignalMouseDownConnector = hvsdk::CNamedType<std::function<void(const ScreenPos&)>, struct SIGNAL_MOUSE_DOWN_CONNECTOR>;

using SignalMouseUp = hvsdk::CNamedType<Signal<void(const ScreenPos&)>, struct SIGNAL_MOUSE_UP>;
using SignalMouseUpConnector = hvsdk::CNamedType<std::function<void(const ScreenPos&)>, struct SIGNAL_MOUSE_UP_CONNECTOR>;

//////////////////////////////////////////////////////////////////////////

}