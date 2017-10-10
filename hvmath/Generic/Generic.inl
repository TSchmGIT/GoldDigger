#pragma once

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif


#include <math.h>
#include <initializer_list>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////

namespace hvmath
{

//////////////////////////////////////////////////////////////////////////

template<typename T>
T Mod(T a, T b)
{
	return a % b;
}

template<>
inline float Mod<float>(float a, float b)
{
	return std::fmod(a, b);
}

template<typename T>
T PingPong(T time, T length)
{
	T lengthDoubled = length * 2;
	T modulo = Mod(time, lengthDoubled); // Clamp between 0 and lengthDoubled

	if (modulo <= length)
	{
		return modulo;
	}
	else
	{
		return lengthDoubled - modulo;
	}
}

template<typename T>
T Max(std::initializer_list<T> iList)
{
	return std::max(iList);
}

template<typename T>
T Min(std::initializer_list<T> iList)
{
	return std::min(iList);
}

template<typename T>
T Clamp(const T& value, const T& lowerLimit, const T& upperLimit)
{
	return std::min(std::max(value, lowerLimit), upperLimit);
}

template<typename T>
T Abs(std::initializer_list<T> iList)
{
	return std::abs(iList);
}

template<typename T>
T Deadzone(const T& value, const T& deadzone)
{
	return std::abs(value) < deadzone ? 0.0f : value;
}


//////////////////////////////////////////////////////////////////////////

} // hvmath