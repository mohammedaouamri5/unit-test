workspace "UNIT-TEST"
    configurations { "Debug", "Release", "Dist" }
    platforms { "x86_64", "x86" }

    -- Include the Vendor folder as a subdirectory for dependencies
    group "Dependencies"
    include "./../../Vendor/spdlog"

project "EX1"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    toolset "gcc"  -- Using the GCC toolchain

    targetdir("bin/%{cfg.platform}_%{cfg.buildcfg}")
    objdir("bin/obj/%{cfg.platform}_%{cfg.buildcfg}")

    files { "EX1.cpp" }

    -- Include directories
    includedirs {
        "./../../Vendor/",
        "./../../Vendor/spdlog/include",
        "./../../Vendor/nlohmann",
        "./../../Source",
        "./../../EX",
        "./../**"
    }

    -- Link against dependencies
    links {
        "spdlog",
        "dl",         -- For dynamic loading on Linux
        "fmt"         -- Assuming fmt is also in your vendor folder
    }

    -- Defines for conditional compilation
    defines { "SPDLOG_COMPILED_LIB", "SPDLOG_ACTIVE_LEVEL" }

    -- Build flags and options specific to the platform
    filter "system:linux"
        buildoptions { "-fPIC" }  -- Ensure position-independent code for shared libraries
        links { "pthread" }        -- Add pthread for Linux if necessary for thread-safe logging

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
 