#pragma once

#include "hvsdk\Meta\StrictTypedef.h"
#include <boost/serialization/strong_typedef.hpp>


using Vector2 = hvmath::Vector2<float>;
using Vector2i = hvmath::Vector2<int>;

using ScreenPos = Vector2;
using WorldPos = Vector2;
