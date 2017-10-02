#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvmath
{

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class CVector2
{

public:
	CVector2() : x(T()), y(T()) {};
	CVector2(T x, T y) : x(x), y(y) {};
	CVector2(const CVector2& vec) = default;
	virtual ~CVector2() = default;

	template<typename U>
	CVector2<T> operator+(const CVector2<U>& vec);
	template<typename U>
	CVector2<T>& operator+=(const CVector2<U>& vec);

	template<typename U>
	CVector2<T> operator*(const U& factor);
	template<typename U>
	CVector2<T>& operator*=(const U& factor);

public:
	T x;
	T y;
};

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
CVector2<T> CVector2<T>::operator+(const CVector2<U>& vec)
{
	return CVector2<T>(x + vec.x, y + vec.y);
}

template<typename T>
template<typename U>
CVector2<T>& CVector2<T>::operator+=(const CVector2<U>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

//////////////////////////////////////////////////////////////////////////

template<typename T>
template<typename U>
CVector2<T> CVector2<T>::operator*(const U& factor)
{
	return CVector2<T>(x * factor, y * factor);
}

template<typename T>
template<typename U>
CVector2<T>& CVector2<T>::operator*=(const U& factor)
{
	x *= factor;
	y *= factor;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

} // hvmath
