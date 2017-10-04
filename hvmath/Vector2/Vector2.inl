#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvmath
{

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class Vector2
{

public:
	Vector2() : x(T()), y(T()) {};
	Vector2(T x, T y) : x(x), y(y) {};
	Vector2(const Vector2& vec) = default;
	virtual ~Vector2() = default;

	template<typename U>
	Vector2<T> operator+(const Vector2<U>& vec);
	template<typename U>
	Vector2<T>& operator+=(const Vector2<U>& vec);

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
Vector2<T> Vector2<T>::operator+(const Vector2<U>& vec)
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
