#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvgs
{

/////////////////////////////////////////////////////////////////////////////
template <typename T>
struct CSingletonBase 
{
	CSingletonBase() = default;
	virtual ~CSingletonBase() = default;
	//CSingletonBase(const& CSingletonBase) = default;

	static T& GetMutable() { return GetActual(); }
	static const T& Get() { return GetActual(); }

private:
	static T& GetActual() { static T t; return t; }
};

} // hvgs
