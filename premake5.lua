workspace "GoldDigger_new"
    architecture "x86"

    configurations
    {
        "Debug",
        "Release",
        "Retail"
    }

outputroot = "ProjectOutput"
outputdir = "/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

targetdirectory = outputroot .. "/bin/" .. outputdir
objdirectory =  outputroot .. "/bin-int/" .. outputdir

project "GameSessionNew"
    location "GameSessionNew"
    kind "ConsoleApp"
    language "C++"

    pchheader "stdafx.h"
    pchsource "GameSessionNew/stdafx.cpp"

    targetdir (targetdirectory .. "/%{prj.name}")
    objdir (objdirectory .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.inl" 
    }

    includedirs
    {
       "%{wks.location}",
       "%{wks.location}/%{prj.name}" 
    }

    libdirs
    {
        outputroot .. "/hvsdk/" .. outputdir,
        outputroot .. "/hvmath/" .. outputdir,
        outputroot .. "/Octree/" .. outputdir,
        outputroot .. "/FastNoiseSIMD/" .. outputdir,
        -- $(SolutionDir)\ProjectOutput\hvmath\$(Configuration)
    }

    links
    {
        "hvsdk",
        "hvmath",
        "Octree",
        "FastNoiseSIMD"
        -- Octree.lib;FastNoiseSIMD.lib;hvmath.lib;hvsdk.lib;
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines 
        {
            "HV_DEBUG",
            "USE_ASSERTS",
            "STATIC_SFML"
        }
        symbols "On"

    filter "configurations:Release"
        defines "HV_RELEASE"
        optimize "On"

    filter "configurations:Retail"
        defines "HV_RETAIL"
        optimize "On"

-- //////////////////////////////////////////////////////////////////////////////////////////

project "hvsdk"
    location "hvsdk"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.h"
    pchsource "hvsdk/stdafx.cpp"

    targetdir (targetdirectory .. "/%{prj.name}")
    objdir (objdirectory .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.inl" 
    }

    includedirs
    {
       "%{wks.location}",
       "%{wks.location}/%{prj.name}" 
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines 
        {
            "HV_DEBUG",
            "USE_ASSERTS",
            "STATIC_SFML"
        }
        symbols "On"

    filter "configurations:Release"
        defines "HV_RELEASE"
        optimize "On"

    filter "configurations:Retail"
        defines "HV_RETAIL"
        optimize "On"

-- //////////////////////////////////////////////////////////////////////////////////////////

project "hvmath"
location "hvmath"
kind "StaticLib"
language "C++"

pchheader "stdafx.h"
pchsource "hvmath/stdafx.cpp"

targetdir (targetdirectory .. "/%{prj.name}")
objdir (objdirectory .. "/%{prj.name}")

files
{
    "%{prj.name}/**.h",
    "%{prj.name}/**.cpp",
    "%{prj.name}/**.inl" 
}

includedirs
{
   "%{wks.location}",
   "%{wks.location}/%{prj.name}" 
}

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "RELEASE"
    optimize "On"

filter "configurations:Retail"
    defines "RELEASE"
    optimize "On"
    
-- //////////////////////////////////////////////////////////////////////////////////////////

project "Octree"
    location "Octree"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.h"
    pchsource "Octree/stdafx.cpp"

    targetdir (targetdirectory .. "/%{prj.name}")
    objdir (objdirectory .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.inl" 
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"

    filter "configurations:Retail"
        defines "RELEASE"
        optimize "On"

-- //////////////////////////////////////////////////////////////////////////////////////////

project "FastNoiseSIMD"
location "FastNoiseSIMD"
kind "StaticLib"
language "C++"

pchheader "stdafx.h"
pchsource "FastNoiseSIMD/stdafx.cpp"

targetdir (targetdirectory .. "/%{prj.name}")
objdir (objdirectory .. "/%{prj.name}")

files
{
    "%{prj.name}/**.h",
    "%{prj.name}/**.cpp",
    "%{prj.name}/**.inl" 
}

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "RELEASE"
    optimize "On"

filter "configurations:Retail"
    defines "RELEASE"
    optimize "On"