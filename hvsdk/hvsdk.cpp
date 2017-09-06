// hvsdk.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "hvsdk.h"


// This is an example of an exported variable
HVSDK_API int nhvsdk=0;

// This is an example of an exported function.
HVSDK_API int fnhvsdk(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see hvsdk.h for the class definition
Chvsdk::Chvsdk()
{
    return;
}
