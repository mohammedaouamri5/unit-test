workspace "UNIT-TEST"
configurations { "Debug", "Release", "Dist" }
platforms { "x86_64", "x86" }
include "EX"

project "TP"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"

targetdir("bin/%{cfg.platform}_%{cfg.buildcfg}")
objdir("bin/obj/%{cfg.platform}_%{cfg.buildcfg}")

files { "Source/**" }
includedirs {
    "EX" , 
    "Vendor/",
    "Vendor/spdlog/include",
    "Vendor/nlohmann", 

}


links {
    "spdlog",
    "dl",
    "fmt",
}

toolset "gcc"
defines { "SPDLOG_COMPILED_LIB", "SPDLOG_ACTIVE_LEVEL" }

group "Dependencies"
    include "Vendor/spdlog"



filter "system:windows"
    systemversion "latest"
    defines { "WINDOWS" }

filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

filter "configurations:Release"
    defines { "RELEASE" }
    optimize "On"
    symbols "On"

filter "configurations:Dist"
    defines { "DIST" }
    optimize "On"
    symbols "Off"

filter "platforms:x86"
architecture "x86"

filter "platforms:x86_64"
architecture "x86_64"


