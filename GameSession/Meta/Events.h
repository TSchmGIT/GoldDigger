#pragma once

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

template<typename T>
using Signal = boost::signals2::signal<T>;

using SignalMouseMove = boost::signals2::signal<void(const ScreenPos&, const ScreenPos&)>;
using SignalMouseMoveConnector = std::function<void(const ScreenPos&, const ScreenPos&)>;

using SignalMouseClicked = boost::signals2::signal<void(const ScreenPos&)>;
using SignalMouseClickedConnector = std::function<void(const ScreenPos&)>;

using SignalMouseDown = Signal<void()>;
using SignalMouseDownConnector = std::function<void()>;

//////////////////////////////////////////////////////////////////////////

}