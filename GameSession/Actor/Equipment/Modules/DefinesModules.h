#pragma once
#include <hvsdk/Meta/NamedType.h>

namespace hvgs
{

//////////////////////////////////////////////////////////////////////////

using ModulePrice = hvsdk::CNamedType<unsigned int, struct MODULE_PRICE_TAG>;

using HullPoints = hvsdk::CNamedType<unsigned int, struct HULL_POINTS_TAG>;

using FuelConsumption = hvsdk::CNamedType<float, struct FUEL_CONSUMPTION_TAG>;
using FuelAmount = hvsdk::CNamedType<unsigned int, struct FUEL_AMOUNT_TAG>;

//////////////////////////////////////////////////////////////////////////

}
