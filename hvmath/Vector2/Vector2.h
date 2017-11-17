#pragma once

#include <SFML\System\Vector2.hpp>

namespace hvmath
{

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class Vector2
{

public:
	Vector2() = default;
	~Vector2() = default;
	Vector2(const T& x, const T& y) : x(x), y(y) {};
	template<typename U>
	Vector2(const Vector2<U>& vec) : x(T(vec.x)), y(T(vec.y)) { };
	Vector2(const sf::Vector2f& vec);
	Vector2(const sf::Vector2u& vec);
	Vector2(const sf::Vector2i& vec);

	Vector2<T>& operator=(const Vector2<T>& other);
	template<typename U> Vector2<T>& operator=(const Vector2<U>& other);

	operator sf::Vector2f() const;
	operator sf::Vector2i() const;
	operator sf::Vector2u() const;

	template<typename U>	static Vector2<T> Scale(const Vector2<T>& a, const Vector2<U>& b);
	template<typename U>	static Vector2<T> ScaleInverse(const Vector2<T>& a, const Vector2<U>& b);
	template<typename U>	static float Dot(const Vector2<T>& a, const Vector2<U>& b);

	static float Magnitude(const Vector2<T>& a);
	static float SqrMagnitude(const Vector2<T>& a);
	static Vector2<T> Normalize(const Vector2<T>& a);
	static Vector2<T> MoveTowards(const Vector2<T>& current, const Vector2<T> target, float maxDelta);

	Vector2<T>& Normalize();


public:
	T x = T(0);
	T y = T(0);
};

//////////////////////////////////////////////////////////////////////////

template<typename T> Vector2<T> operator-(const Vector2<T>& vec);

template<typename T, typename U> bool operator==(const Vector2<T>& vec1, std::initializer_list<U> initList);
template<typename T, typename U> bool operator==(const Vector2<T>& vec1, const Vector2<U>& vec2);
template<typename T, typename U> bool operator!=(const Vector2<T>& vec1, const Vector2<U>& vec2);

template<typename T, typename U> Vector2<T> operator+(const Vector2<T>& left, const Vector2<U>& right);
template<typename T, typename U> Vector2<T>& operator+=(Vector2<T>& left, const Vector2<U>& right);

template<typename T, typename U> Vector2<T> operator-(const Vector2<T>& left, const Vector2<U>& right);
template<typename T, typename U> Vector2<T>& operator-=(Vector2<T>& left, const Vector2<U>& right);

template<typename T, typename U> Vector2<T> operator*(const Vector2<T>& left, const U& right);
template<typename T, typename U> Vector2<T> operator*(const U& left, const Vector2<T>& right);
template<typename T, typename U> Vector2<T>& operator*=(Vector2<T>& left, const U& right);

template<typename T, typename U> Vector2<T> operator/(const Vector2<T>& left, const U& right);
template<typename T, typename U> Vector2<T>& operator/=(Vector2<T>& left, const U& right);

/////////////////////////////////////////////////////////////////////////////

#include "Vector2.inl"

} // hvmath
