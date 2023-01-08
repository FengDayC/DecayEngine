workspace "Decay"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Decay/vendor/GLFW/include"

include "Decay/vendor/GLFW"

project "Decay"

    location "Decay"
    kind "Sharedlib"
    language "C++"
    targetdir ("bin/"..outputdir.."/%{prj.name}")

    pchheader "dcpch.h"
    pchsource "Decay/src/dcpch.cpp"

    objdir ("bin-int/"..outputdir.."/%{prj.name}")
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }
    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "DECAY_PLATFORM_WINDOWS",
            "DECAY_BUILD_DLL",
            "_WinBuild"
        }
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
        }

    filter "configurations:Debug"
        defines "DC_DEBUG"
		buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "DC_RELEASE"
		buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "DC_DIST"
		buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/"..outputdir.."/%{prj.name}")

    objdir ("bin-int/"..outputdir.."/%{prj.name}")
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    includedirs
    {
        "Decay/vendor/spdlog/include",
        "Decay/src"
    }   

    links
    {
        "Decay"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "DECAY_PLATFORM_WINDOWS",
            "_WinBuild"
        }

    filter "configurations:Debug"
        defines "DC_DEBUG"
		buildoptions "/MDd"
        symbols "On"
    
    filter "configurations:Release"
        defines "DC_RELEASE"
		buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist"
        defines "DC_DIST"
		buildoptions "/MD"
        optimize "On"