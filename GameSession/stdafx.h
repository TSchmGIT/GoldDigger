// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <windows.h>

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include <chrono>

#include <memory>
#include <boost/unordered_map.hpp>
#include <boost/pointer_cast.hpp>

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// External libs
#include <SFML/Graphics.hpp>

#include <FastNoiseSIMD/FastNoiseSIMD.h>

//////////////////////////////////////////////////////////////////////////
// Haven libs
#include <hvsdk/Meta/DefinesSTL.h>
#include <hvsdk/Meta/Log.h>
#include <hvsdk/Meta/Assert.h>
#include <hvsdk/Meta/ObjectPool.h>

#include <hvmath/Generic/Generic.inl>
#include <hvmath/Vector2/Vector2.h>

//////////////////////////////////////////////////////////////////////////
// Haven GameSession
#include "GameSession/Meta/Defines.h"
#include "GameSession/Meta/TrackTime.h"

#include "GameSession/Time/DefinesTime.h"
#include "GameSession/Rendering/RenderEnums.h"

#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Manager/PerformanceManager.h"
