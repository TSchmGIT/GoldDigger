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

#include <chrono>

#include <memory>
#include <boost/unordered_map.hpp>

//////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

#include <hvsdk/Meta/DefinesSTL.h>
#include <hvsdk/Meta/Log.h>
#include <hvsdk/Meta/Assert.h>
#include <hvsdk/Meta/ObjectPool.h>

#include <hvmath/Vector2/Vector2.inl>
#include <hvmath/Generic/Generic.inl>

#include "Meta/Defines.h"
#include "Meta/TrackTime.h"

#include "Time/DefinesTime.h"

#include "GameSession/Manager/SingletonBase.h"
#include "GameSession/Manager/PerformanceManager.h"
