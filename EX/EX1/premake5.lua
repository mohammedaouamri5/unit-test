workspace "UNIT-TEST"
    configurations { "Debug", "Release", "Dist" }
    platforms { "x86_64", "x86" }


project "EX1"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"  -- Using the GCC toolchain

    targetdir("bin/%{cfg.platform}_%{cfg.buildcfg}")
    objdir("bin/obj/%{cfg.platform}_%{cfg.buildcfg}")

    files { "EX1.cpp" , "./../../Source/loader.cpp" }

    -- Include directories
    includedirs {
        "./../../Vendor/",
        "./../../Vendor/nlohmann",
        "./../../Source",
        "./../../EX",
        "/usr/include/fmt", 
        "./../**"
    }

    -- Link against dependencies
    links {
        "dl",         -- For dynamic loding on Linux
    "fmt", 
    }

    -- Defines for conditionl compilation

    -- Build flags and options specific to the platform
    filter "system:linux"

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    -- Configuration-specific settings
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

    -- Platform-specific settings
    filter "platforms:x86"
        architecture "x86"

    filter "platforms:x86_64"
        architecture "x86_64"
 
