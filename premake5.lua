workspace "GoldDigger"
    architecture "x64"

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

project "GameSession"
    location "src/GameSession"
    kind "ConsoleApp"
    language "C++"

    pchheader "stdafx.h"
    pchsource "src/GameSession/stdafx.cpp"

    targetdir (targetdirectory .. "/%{prj.name}")
    objdir (objdirectory .. "/%{prj.name}")

    files
    {
        "src/%{prj.name}/**.h",
        "src/%{prj.name}/**.cpp",
        "src/%{prj.name}/**.inl" 
    }

    defines
    {
        "SFML_STATIC",
        "STATIC_SFML",
        "SFML_USE_STATIC_STD_LIBS"
    }

    includedirs
    {
        "External/SFML/include",
        "External/boost",

        "External/FastNoiseSIMD",

        "%{wks.location}/src/",
        "%{wks.location}/src/%{prj.name}"
    }

    libdirs
    {
        "External/SFML/lib",
        "External/boost/libs",
        targetdirectory .. "/FastNoiseSIMD"
    }

    links
    {
        -- SFML DEFAULT LINKS
        "opengl32",
        "freetype",
        "winmm",
        "gdi32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32",
        -- END SFML DEFAULT LINKS

        "hvsdk",
        "hvmath",
        "FastNoiseSIMD"
        -- Octree.lib;FastNoiseSIMD.lib;hvmath.lib;hvsdk.lib;
    }

    filter "system:windows"
        cppdialect "C++17"
        -- staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines 
        {
            "DEBUG",
            "HV_DEBUG",
            "USE_ASSERTS"
        }

        links
        {
            "sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-system-s-d",
			"sfml-audio-s-d",
			"sfml-network-s-d"
        }

        symbols "On"

    filter "configurations:Release"
        defines
        {
            "RELEASE",
            "NDEBUG",
            "HV_RELEASE"
        }
        optimize "On"

        links
		{	
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			"sfml-audio-s",
			"sfml-network-s"
		}

    filter "configurations:Retail"
        defines
        {
            "RELEASE",
            "NDEBUG",
            "HV_RETAIL"
        }
        optimize "On"

        links
		{	
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			"sfml-audio-s",
			"sfml-network-s"
		}

-- //////////////////////////////////////////////////////////////////////////////////////////

project "hvsdk"
    location "src/hvsdk"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.h"
    pchsource "src/hvsdk/stdafx.cpp"

    targetdir (targetdirectory .. "/%{prj.name}")
    objdir (objdirectory .. "/%{prj.name}")

    files
    {
        "src/%{prj.name}/**.h",
        "src/%{prj.name}/**.cpp",
        "src/%{prj.name}/**.inl" 
    }

    includedirs
    {
        "External/boost",
        "%{wks.location}/src",
        "%{wks.location}/src/%{prj.name}" 
    }

    filter "system:windows"
        cppdialect "C++17"
        -- staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines 
        {
            "HV_DEBUG",
            "USE_ASSERTS"
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
location "src/hvmath"
kind "StaticLib"
language "C++"

pchheader "stdafx.h"
pchsource "src/hvmath/stdafx.cpp"

targetdir (targetdirectory .. "/%{prj.name}")
objdir (objdirectory .. "/%{prj.name}")

files
{
    "src/%{prj.name}/**.h",
    "src/%{prj.name}/**.cpp",
    "src/%{prj.name}/**.inl" 
}

libdirs
{
    "External/SFML/lib"
}

includedirs
{
    "External/SFML/include",
    "%{wks.location}/src",
    "%{wks.location}/src/%{prj.name}" 
}

defines
{
    "SFML_STATIC",
    "STATIC_SFML",
    "SFML_USE_STATIC_STD_LIBS"
}

filter "system:windows"
    cppdialect "C++17"
    -- staticruntime "On"
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
-- //////////////////////////////////////////////////////////////////////////////////////////

-- workspace "FastNoiseSIMD"
--     location "External/FastNoiseSIMD"
--     architecture "x64"

--     configurations
--     {
--         "Debug",
--         "Release"
--     }

-- project "FastNoiseSIMD"
--     location "External/FastNoiseSIMD"
--     kind "StaticLib"
--     language "C++"

-- targetdir (targetdirectory .. "/%{prj.name}")
-- objdir (objdirectory .. "/%{prj.name}")

-- files
-- {
--     "%{prj.location}/**.h",
--     "%{prj.location}/**.cpp",
--     "%{prj.location}/**.inl",
--     "%{prj.location}/**.c" 
-- }

-- filter "system:windows"
--     cppdialect "C++17"
--     -- staticruntime "On"
--     systemversion "latest"

-- filter "configurations:Debug"
--     defines "DEBUG"
--     symbols "On"

-- filter "configurations:Release"
--     defines "RELEASE"
--     optimize "On"
