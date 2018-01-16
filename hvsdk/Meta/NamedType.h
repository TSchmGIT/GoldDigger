#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvsdk
{

/////////////////////////////////////////////////////////////////////////////

#define  NamedTemplate template<typename T, typename TAG>
#define NamedType hvsdk::CNamedType<T, TAG>

NamedTemplate
class CNamedType
{

public:
	explicit CNamedType() : m_Value() {}
	explicit CNamedType(const T& value) : m_Value(value) {}
	constexpr const T& get() const { return m_Value; }
	constexpr T& get() { return m_Value; }


	explicit operator T() { return m_Value; }

	constexpr NamedType& operator +=(const NamedType& rhs) { m_Value += rhs.m_Value; return *this; }
	constexpr NamedType& operator -=(const NamedType& rhs) { m_Value -= rhs.m_Value; return *this; }
	constexpr NamedType& operator *=(const NamedType& rhs) { m_Value *= rhs.m_Value; return *this; }
	constexpr NamedType& operator /=(const NamedType& rhs) { m_Value *= rhs.m_Value; return *this; }

	size_t hash_code() const noexcept { return (m_Value.hash_code()); }

private:
	T m_Value;

};

/////////////////////////////////////////////////////////////////////////////

NamedTemplate constexpr NamedType operator +(const NamedType& lhs, const NamedType& rhs) { return NamedType(lhs.get() + rhs.get()); }
NamedTemplate constexpr NamedType operator -(const NamedType& lhs, const NamedType& rhs) { return NamedType(lhs.get() - rhs.get()); }
NamedTemplate constexpr NamedType operator *(const NamedType& lhs, const NamedType& rhs) { return NamedType(lhs.get() * rhs.get()); }
NamedTemplate constexpr NamedType operator /(const NamedType& lhs, const NamedType& rhs) { return NamedType(lhs.get() / rhs.get()); }

NamedTemplate constexpr bool operator ==(const NamedType& lhs, const NamedType& rhs) { return lhs.get() == rhs.get(); }
NamedTemplate constexpr bool operator !=(const NamedType& lhs, const NamedType& rhs) { return lhs.get() != rhs.get(); }

NamedTemplate constexpr bool operator >(const NamedType& lhs, const NamedType& rhs) { return lhs.get() > rhs.get(); }
NamedTemplate constexpr bool operator >=(const NamedType& lhs, const NamedType& rhs) { return lhs.get() >= rhs.get(); }
NamedTemplate constexpr bool operator <(const NamedType& lhs, const NamedType& rhs) { return lhs.get() < rhs.get(); }
NamedTemplate constexpr bool operator <=(const NamedType& lhs, const NamedType& rhs) { return lhs.get() <= rhs.get(); }

//////////////////////////////////////////////////////////////////////////

} // hvsdk

namespace boost
{
NamedTemplate struct hash<NamedType>
{
	constexpr size_t operator()(const NamedType& namedType) const
	{
		return boost::hash<T>()(namedType.get());
	}
};
}