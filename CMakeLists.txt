cmake_minimum_required(VERSION 3.14...4.0)

project(9002Game LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

# Fix for glad.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Find git revision.
include(FindGit OPTIONAL)
if (GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/.git)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE VERSION_GIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# PROJECT_SOURCES is a list of all the sources files in this project. No more manually adding each source file.
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(9002Game "${PROJECT_SOURCES}")

# TODO: Disable console on windows release builds.

# Macro definitions
target_compile_definitions(9002Game PRIVATE
    $<$<CONFIG:Debug>:DEBUG>

    $<$<CONFIG:RelWithDebInfo>:DEBUG>
    $<$<CONFIG:RelWithDebInfo>:REL_WITH_DEB_INFO>

    $<$<CONFIG:Release>:RELEASE>

    $<$<CONFIG:MinSizeRel>:RELEASE>
    $<$<CONFIG:MinSizeRel>:MIN_SIZE_REL>
    VERSION_GIT="${VERSION_GIT}"
)

# Basic platform detection
if(WIN32)
    message("Platform: Windows.")
    target_compile_definitions(9002Game PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    message("Platform: Unix-like system.")
    target_compile_definitions(9002Game PRIVATE PLATFORM_UNIX)
endif()
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    message("Targeting ARM64 architecture.")
    target_compile_definitions(9002Game PRIVATE PLATFORM_ARM64)
endif()

# Target compile options
option(TREAT_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
if(TREAT_WARNINGS_AS_ERRORS)
    target_compile_options(9002Game PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX -D_CRT_SECURE_NO_WARNINGS>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror -D_CRT_SECURE_NO_WARNINGS>
    )
else()
    target_compile_options(9002Game PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
    )
endif()

# Copy the res/ folder to the output binary destination.
if(MSVC)
    add_custom_target(copy_data ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/res
    )
else()
    add_custom_target(copy_data ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res
    )
endif()

if(MSVC)
    set_property(TARGET 9002Game PROPERTY
        CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

add_dependencies(9002Game copy_data)

add_subdirectory(lib)

add_dependencies(9002Game spdlog)
add_dependencies(9002Game glfw)
add_dependencies(9002Game glad)
add_dependencies(9002Game glm)
add_dependencies(9002Game imgui)
add_dependencies(9002Game EnTT::EnTT)   # EnTT
add_dependencies(9002Game OpenAL)       # OpenALSoft
add_dependencies(9002Game Catch2)
add_dependencies(9002Game Jolt)         # JoltPhysics

target_include_directories(9002Game PRIVATE src)

target_include_directories(spdlog PRIVATE include)
target_include_directories(glad PRIVATE include)

target_link_libraries(9002Game PRIVATE glfw glad spdlog glm imgui EnTT::EnTT OpenAL Catch2 Jolt)
