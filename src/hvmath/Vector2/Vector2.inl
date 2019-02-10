#pragma once

//////////////////////////////////////////////////////////////////////////

template<typename T> constexpr Vector2<T>::Vector2(const sf::Vector2f& vec) : x(T(vec.x)), y(T(vec.y)) { }
template<typename T> constexpr Vector2<T>::Vector2(const sf::Vector2i& vec) : x(T(vec.x)), y(T(vec.y)) { }
template<typename T> constexpr Vector2<T>::Vector2(const sf::Vector2u& vec) : x(T(vec.x)), y(T(vec.y)) { }

////////////////////////////////////////////////////////////////////////////

template<typename T> constexpr Vector2<T>::operator sf::Vector2f() const { return sf::Vector2f(float(x), float(y)); }
template<typename T> constexpr Vector2<T>::operator sf::Vector2i() const { return sf::Vector2i(int(x), int(y)); }
template<typename T> constexpr Vector2<T>::operator sf::Vector2u() const { return sf::Vector2u(unsigned int(x), unsigned int(y)); }

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
constexpr Vector2<T> Vector2<T>::Scale(const Vector2<T>& a, const Vector2<U>& b)
{
	return Vector2<T>(a.x * b.x, a.y * b.y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
constexpr Vector2<T> Vector2<T>::ScaleInverse(const Vector2<T>& a, const Vector2<U>& b)
{
	return Vector2<T>(a.x / b.x, a.y / b.y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
constexpr float Vector2<T>::Dot(const Vector2<T>& a, const Vector2<U>& b)
{
	return a.x * b.x + a.y * b.y;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr float Vector2<T>::Magnitude(const Vector2<T>& a)
{
	return Sqrt(a.x * a.x + a.y * a.y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr float Vector2<T>::SqrMagnitude(const Vector2<T>& a)
{
	return a.x * a.x + a.y * a.y;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr Vector2<T> Vector2<T>::Normalize(const Vector2<T>& a)
{
	if (a.x == T(0) && a.y == T(0))
	{
		return Vector2<T>(0.0f, 0.0f);
	}

	return a / Magnitude(a);
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr Vector2<T> Vector2<T>::MoveTowards(const Vector2<T>& current, const Vector2<T> target, float maxDelta)
{
	Vector2<T> delta = target - current;
	if (Vector2<T>::SqrMagnitude(target - current) <= maxDelta * maxDelta)
	{
		return target;
	}

	return current + delta.Normalize() * maxDelta;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
constexpr bool Vector2<T>::DistanceCheck(const Vector2<T>& a, const Vector2<U>& b, float distance)
{
	return SqrMagnitude(a - b) < distance * distance;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr Vector2<T>& Vector2<T>::Normalize()
{
	if (x != T(0) || y != T(0))
	{
		*this = *this / Magnitude(*this);
	}

	return *this;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr Vector2<T>& Vector2<T>::operator=(const Vector2<T>& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
constexpr Vector2<T>& Vector2<T>::operator=(const Vector2<U>& other)
{
	x = T(other.x);
	y = T(other.y);

	return *this;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
constexpr Vector2<T> operator-(const Vector2<T>& vec)
{
	return Vector2<T>(-vec.x, -vec.y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr bool operator==(const Vector2<T>& vec1, std::initializer_list<U> initList)
{
	ASSERT_OR_EXECUTE(initList.size() == 2, return false);

	return vec1.x == initList[0] && vec1.y == initList[1];
}

template<typename T, typename U>
constexpr bool operator==(const Vector2<T>& vec1, const Vector2<U>& vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

template<typename T, typename U>
constexpr bool operator!=(const Vector2<T>& vec1, const Vector2<U>& vec2)
{
	return !(*vec1 == vec2);
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<U>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T, typename U>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<U>& right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<U>& right)
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}

template<typename T, typename U>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<U>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T> operator*(const Vector2<T>& left, const U& right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T> operator*(const U& left, const Vector2<T>& right)
{
	return Vector2<T>(left * right.x, left * right.y);
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T>& operator*=(Vector2<T>& left, const U& right)
{
	left.x *= right;
	left.y *= right;
	return left;
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T> operator/(const Vector2<T>& left, const U& right)
{
	return Vector2<T>(left.x / right, left.y / right);
}

//////////////////////////////////////////////////////////////////////////

template<typename T, typename U>
constexpr Vector2<T>& operator/=(Vector2<T>& left, const U& right)
{
	left.x /= right;
	left.y /= right;
	return left;
}
