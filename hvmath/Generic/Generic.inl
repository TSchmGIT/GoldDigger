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

#include "hvmath/Vector2/Vector2.h"

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
constexpr T Mod(T value, T operand)
{
	return value % operand;
}

template<>
inline float Mod<float>(float value, float operand)
{
	return std::fmod(value, operand);
}

template<typename T>
constexpr T PingPong(T time, T length)
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

template<typename TOutput, typename T>
constexpr TOutput Floor(T value)
{
	return TOutput(std::floor(value));
}

template<typename TOutput, typename T>
constexpr TOutput Ceil(T value)
{
	return TOutput(std::ceil(value));
}

template<typename T>
constexpr T Max(std::initializer_list<T> iList)
{
	return std::max(iList);
}

template<typename T>
constexpr T Min(std::initializer_list<T> iList)
{
	return std::min(iList);
}

template<typename T>
constexpr T Clamp(const T& value, const T& lowerLimit, const T& upperLimit)
{
	return std::min(std::max(value, lowerLimit), upperLimit);
}

template<typename T>
constexpr T Abs(const T& value)
{
	return std::abs(value);
}

template<>
constexpr hvmath::Vector2<float> Abs<hvmath::Vector2<float>>(const hvmath::Vector2<float>& value)
{
	return hvmath::Vector2<float>(std::abs(value.x), std::abs(value.y));
}

template<typename T>
constexpr T Sign(const T& value)
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
constexpr T Deadzone(const T& value, const T& deadzone)
{
	return std::abs(value) < deadzone ? 0.0f : value;
}


//////////////////////////////////////////////////////////////////////////

} // hvmath