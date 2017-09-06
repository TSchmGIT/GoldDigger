#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvsdk
{

/////////////////////////////////////////////////////////////////////////////
template <typename T>
struct CSingletonBase 
{
	static T& GetMutable() { return GetActual(); }
	static const T& Get() { return GetActual(); }

private:
	static T& GetActual() { static T t; return t; }
};

} // hvsdk
