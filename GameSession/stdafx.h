// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <windows.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#pragma warning (push)
#pragma warning (disable : 4996)
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include <chrono>
#include <numeric>

#include <array>
#include <bitset>
#include <memory>

#include <optional>

#include <vector>
#include <queue>
#include <set>

#include <boost/unordered_map.hpp>
#include <boost/pointer_cast.hpp>

#include <boost/signals2.hpp>
#pragma warning (pop)

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// External libs
#include <SFML/Graphics.hpp>

#include <FastNoiseSIMD/FastNoiseSIMD.h>

//////////////////////////////////////////////////////////////////////////
// Haven libs
#include "GameSession/Config/config_default.h"

#include <hvsdk/Meta/NamedType.h>
#include <hvsdk/Meta/DefinesSTL.h>
#include <hvsdk/Meta/Log.h>
#include <hvsdk/Meta/Assert.h>
#include <hvsdk/Meta/ObjectPool.h>

#include <hvmath/Generic/Generic.inl>
#include <hvmath/Vector2/Vector2.h>

//////////////////////////////////////////////////////////////////////////
// Haven GameSession
#include "GameSession/Data/DataDefines.h"

#include "GameSession/Meta/Defines.h"
#include "GameSession/Meta/Events.h"
#include "GameSession/Meta/TrackTime.h"

#include "GameSession/Time/DefinesTime.h"
#include "GameSession/Rendering/RenderEnums.h"

#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Manager/PerformanceManager.h"
