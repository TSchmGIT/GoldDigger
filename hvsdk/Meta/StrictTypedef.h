#pragma once

/////////////////////////////////////////////////////////////////////////////

namespace hvsdk
{

/////////////////////////////////////////////////////////////////////////////

template<class base_type, class tag>
class CStrictTypedef : public base_type
{
public:
	explicit CStrictTypedef(base_type i = base_type()) : base_type(i) {}
};

/////////////////////////////////////////////////////////////////////////////

} // hvsdk