#pragma once

#include <math.h>

/////////////////////////////////////////////////////////////////////////////

namespace hvmath
{

/////////////////////////////////////////////////////////////////////////////

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
class Vector2
{

public:
	Vector2() = default;
	~Vector2() = default;
	Vector2(T x, T y) : x(x), y(y) {};


	template<typename U>
	bool operator==(const Vector2<U>& vec) const;
	template<typename U>
	bool operator!=(const Vector2<U>& vec);

	template<typename U>
	Vector2<T> operator+(const Vector2<U>& vec) const;
	template<typename U>
	Vector2<T>& operator+=(const Vector2<U>& vec);

	template<typename U>
	Vector2<T> operator-(const Vector2<U>& vec) const;
	template<typename U>
	Vector2<T>& operator-=(const Vector2<U>& vec);

	template<typename U>
	Vector2<T> operator*(const U& factor);
	template<typename U>
	Vector2<T>& operator*=(const U& factor);

	operator sf::Vector2f() const;
	operator sf::Vector2i() const;
	operator sf::Vector2u() const;

public:
	T x;
	T y;
};

//////////////////////////////////////////////////////////////////////////

template<typename T>
Vector2<T>::operator sf::Vector2u() const
{
	return sf::Vector2u(x, y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
Vector2<T>::operator sf::Vector2i() const
{
	return sf::Vector2i(x, y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
Vector2<T>::operator sf::Vector2f() const
{
	return sf::Vector2f(x, y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
bool Vector2<T>::operator==(const Vector2<U>& vec) const
{
	return x == vec.x && y == vec.y;
}

template<typename T>
template<typename U>
bool Vector2<T>::operator!=(const Vector2<U>& vec)
{
	return !(*this == vec);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
Vector2<T> Vector2<T>::operator+(const Vector2<U>& vec) const
{
	return Vector2<T>(x + vec.x, y + vec.y);
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator+=(const Vector2<U>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
Vector2<T> Vector2<T>::operator-(const Vector2<U>& vec) const
{
	return Vector2<T>(x - vec.x, y - vec.y);
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator-=(const Vector2<U>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}


//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
Vector2<T> Vector2<T>::operator*(const U& factor)
{
	return Vector2<T>(x * factor, y * factor);
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator*=(const U& factor)
{
	x *= factor;
	y *= factor;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

} // hvmath
