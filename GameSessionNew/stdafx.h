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


#include <vector>
#include <queue>
#include <set>

#include <boost/optional.hpp>

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
#include "GameSessionNew/Config/config_default.h"

#include <hvsdk/Meta/NamedType.h>
#include <hvsdk/Meta/DefinesSTL.h>
#include <hvsdk/Meta/Log.h>
#include <hvsdk/Meta/Assert.h>
#include <hvsdk/Meta/ObjectPool.h>

#include <hvmath/Generic/Generic.inl>
#include <hvmath/Vector2/Vector2.h>

//////////////////////////////////////////////////////////////////////////
// Haven GameSessionNew
#include "GameSessionNew/Data/DataDefines.h"

#include "GameSessionNew/Meta/Defines.h"
#include "GameSessionNew/Meta/Events.h"
#include "GameSessionNew/Meta/TrackTime.h"

#include "GameSessionNew/Time/DefinesTime.h"
#include "GameSessionNew/Rendering/RenderEnums.h"

#include "GameSessionNew/Manager/SingletonBase.h"
#include "GameSessionNew/Manager/PerformanceManager.h"
