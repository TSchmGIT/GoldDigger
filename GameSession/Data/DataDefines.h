#pragma once
#include <hvsdk/JSON/json.hpp>
#include <hvsdk/Meta/NamedType.h>

//////////////////////////////////////////////////////////////////////////

using ModuleGUID = hvsdk::CNamedType<int, struct MODULE_GUID>; ///< GUID of a equipable module
#define MODULE_GUID_INVALID ModuleGUID(-1)

using ModuleID = hvsdk::CNamedType<int, struct MODULE_ID>; ///< ID of a equipable module
#define MODULE_ID_INVALID ModuleID(-1)

//////////////////////////////////////////////////////////////////////////

namespace hvda
{

using JSON = nlohmann::json;

}
