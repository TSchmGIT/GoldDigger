// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#else
#define WIN64_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif
// Windows Header Files:
#include <windows.h>

#include <string>
#include <iostream>
#include <vector>

#include <chrono>
#include <memory>
#include <boost/unordered_map.hpp>

//////////////////////////////////////////////////////////////////////////

#include "Meta/Assert.h"
#include "Meta/DefinesSTL.h"
#include "Meta/Log.h"