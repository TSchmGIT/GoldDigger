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
inline T Sqrt(const T& value)
{
	return std::sqrt(value);
}

template<typename T>
inline T Mod(T value, T operand)
{
	return value % operand;
}

template<>
inline float Mod<float>(float value, float operand)
{
	return std::fmod(value, operand);
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

template<typename T, typename TOutput>
inline TOutput Floor(T value)
{
	return TOutput(std::floor(value));
}

template<typename T, typename TOutput>
inline TOutput Ceil(T value)
{
	return TOutput(std::ceil(value));
}

template<typename T>
inline T Max(std::initializer_list<T> iList)
{
	return std::max(iList);
}

template<typename T>
inline T Min(std::initializer_list<T> iList)
{
	return std::min(iList);
}

template<typename T>
inline T Clamp(const T& value, const T& lowerLimit, const T& upperLimit)
{
	return std::min(std::max(value, lowerLimit), upperLimit);
}

template<typename T>
inline T Abs(std::initializer_list<T> iList)
{
	return std::abs(iList);
}

template<typename T>
inline T Sign(const T& value)
{
	if (value > 0)
	{
		return T(1);
	}
	else if (value < 0)
	{
		return T(-1);
	}
	else
	{
		return T(0);
	}
}

template<typename T>
inline T Deadzone(const T& value, const T& deadzone)
{
	return std::abs(value) < deadzone ? 0.0f : value;
}


//////////////////////////////////////////////////////////////////////////

} // hvmath