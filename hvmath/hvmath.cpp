// hvmath.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "hvmath.h"


// This is an example of an exported variable
HVMATH_API int nhvmath=0;

// This is an example of an exported function.
HVMATH_API int fnhvmath(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see hvmath.h for the class definition
Chvmath::Chvmath()
{
    return;
}
