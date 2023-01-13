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
IncludeDir["Glad"] = "Decay/vendor/Glad/include"
IncludeDir["ImGui"] = "Decay/vendor/ImGui"
IncludeDir["glm"] = "Decay/vendor/GLM"
IncludeDir["stb_image"] = "Decay/vendor/stb_image"

include "Decay/vendor/GLFW"
include "Decay/vendor/Glad"
include "Decay/vendor/ImGui"

project "Decay"

    location "Decay"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
	staticruntime "on"
    targetdir ("bin/"..outputdir.."/%{prj.name}")

    pchheader "dcpch.h"
    pchsource "Decay/src/dcpch.cpp"

    objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/GLM/glm/**.h",
		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl"
    }
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
    }
    links
    {
		"ImGui",
		"Glad",
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "DECAY_PLATFORM_WINDOWS",
            "DECAY_BUILD_DLL",
            "_WinBuild",
			"GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines 
		{
			"DC_DEBUG",
			"DECAY_ENABLE_ASSERTS"
		}
		buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "DC_RELEASE"
		buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "DC_DIST"
		buildoptions "/MD"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
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
        "Decay/src",
		"Decay/vendor",
		"%{IncludeDir.glm}"
    }   

    links
    {
        "Decay"
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "DECAY_PLATFORM_WINDOWS",
			"_WinBuild"
        }

    filter "configurations:Debug"
        defines "DC_DEBUG"
		buildoptions "/MDd"
        symbols "on"
    
    filter "configurations:Release"
        defines "DC_RELEASE"
		buildoptions "/MD"
        optimize "on"
    
    filter "configurations:Dist"
        defines "DC_DIST"
		buildoptions "/MD"
        optimize "on"