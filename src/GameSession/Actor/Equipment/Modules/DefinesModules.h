#pragma once
#include <hvsdk/Meta/NamedType.h>

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

using HullPoints = hvsdk::CNamedType<hvuint, struct HULL_POINTS_TAG>;

using FuelConsumption = hvsdk::CNamedType<float, struct FUEL_CONSUMPTION_TAG>;
using FuelAmount = hvsdk::CNamedType<float, struct FUEL_AMOUNT_TAG>;

//////////////////////////////////////////////////////////////////////////

}
