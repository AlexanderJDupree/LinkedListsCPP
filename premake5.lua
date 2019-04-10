-- File: premake5.lua

-- Brief: Build script for the premake build system. Run 'premake5 gmake' to 
--        build GNU specific makefiles. 

-- Author: Alexander DuPree

-- WORKSPACE CONFIGURATION --
workspace "LinkedList"
    configurations { "debug", "release" }
    platforms { "single", "double" }

    if _ACTION == "clean" then
        os.rmdir("bin/")
        os.rmdir("gmake/")
        os.rmdir("gmake2/")
    end

    local project_action = "UNDEFINED"
    if _ACTION ~= nill then project_action = _ACTION end

    location (project_action)

    -- PLATFORM CONFIGURATIONS --
    
    -- COMPILER/LINKER CONFIG --
    flags "FatalWarnings"
    warnings "Extra"

    filter "configurations:debug*"   
        defines { "DEBUG", "MOCKING_ENABLED" } 
        symbols "On"

    filter "configurations:release*" 
        defines { "NDEBUG" } 
        optimize "On"

    filter "platforms:single"
        defines { "LINEAR_LINKED_LIST" }

    filter "platforms:double"
        defines { "DOUBLE_LINKED_LIST" }

    filter "toolset:gcc"
        buildoptions { 
            "-Wall", "-Wextra", "-Werror", "-std=c++11"
        }

    filter {} -- close filter

project "LinkedList"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/lib"
    targetname "LinkedList_%{cfg.shortname}"

    local source = "src/"
    local include = "include/"

    files (source .. "linear_linked_list.hpp")
    includedirs { source, include }

project "example"
    kind "ConsoleApp"
    language "C++"
    links "LinkedList"
    targetdir "bin/example/"
    targetname  "example_%{cfg.shortname}"

    local source = "example/"
    local include = "release/"

    files (source .. "example.cpp")
    includedirs{ include }

project "Tests"
    kind "ConsoleApp"
    language "C++"
    links "LinkedList"
    targetdir "bin/tests/"
    targetname "run_tests"

    local include  = "include/"
    local test_src = "tests/"
    local test_inc = "third_party/"

    files (test_src .. "**.cpp")

    includedirs { test_inc, include, "src/" }

    postbuildcommands ".././bin/tests/run_tests"

    filter {} -- close filter

