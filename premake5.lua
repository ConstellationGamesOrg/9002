workspace "9002"
   configurations { "Debug", "Release" }
   platforms { "Windows-x86_64", "Linux-x86_64"}

project "9002Game"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    -- Tools (for quickly using map editors or whatever else)
    -- Could be put here with no symbols, but also no optimizations in future

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    filter "platforms:Windows-x86_64"
        system "Windows"
        architecture "x86_64"
        defines { "PLATFORM_WINDOWS=1" }
    
    filter "platforms:Linux-x86_64"
        system "Linux"
        architecture "x86_64"
        defines { "PLATFORM_LINUX=1" }
