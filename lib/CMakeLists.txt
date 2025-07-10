include(FetchContent)

find_package(OpenGL REQUIRED)

#- GLFW ---------------------------------------------------------------------

message("Fetching glfw")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")

# NOTE: Wayland ON causes runtime errors... again.
# "libdecor-gtk-WARNING: Failed to initialize GTK"
# "Failed to load plugin 'libdecor-gtk.so': failed to init"
set(GLFW_FORCE_WAYLAND OFF CACHE BOOL "")
set(GLFW_FORCE_X11 ON CACHE BOOL "")

if(UNIX AND NOT APPLE AND GLFW_FORCE_WAYLAND)
	set(GLFW_BUILD_WAYLAND ON CACHE BOOL "")
	set(GLFW_BUILD_X11 OFF CACHE BOOL "")
endif()
if(UNIX AND NOT APPLE AND GLFW_FORCE_X11)
	set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "")
	set(GLFW_BUILD_X11 ON CACHE BOOL "")
endif()

FetchContent_MakeAvailable(glfw)

#- GLAD ---------------------------------------------------------------------

message("Fetching glad")

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        origin/master
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=4.5" CACHE STRING "API type/version pairs, like \"gl=4.5\", no version means latest")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
set(GLAD_EXTENSIONS "GL_ARB_bindless_texture" CACHE STRING "Extensions to take into consideration when generating the bindings")
FetchContent_MakeAvailable(glad)

#- SPDLOG -------------------------------------------------------------------

message("Fetching spdlog")

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.15.3
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(spdlog)

#- GLM ----------------------------------------------------------------------

message("Fetching glm")

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(glm)
target_compile_definitions(glm INTERFACE GLM_FORCE_SILENT_WARNINGS)

#- STB ----------------------------------------------------------------------

message("Fetching stb")

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(stb)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})

#- IMGUI --------------------------------------------------------------------

message("Fetching ImGui docking branch")

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        origin/docking
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(imgui)

add_library(imgui
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

#- EnTT ---------------------------------------------------------------------

message("Fetching EnTT")

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(EnTT)

#- OPENAL SOFT --------------------------------------------------------------

message("Fetching OpenAL Soft")

FetchContent_Declare(
    OpenALSoft
    GIT_REPOSITORY https://github.com/kcat/openal-soft.git
    GIT_TAG        1.24.3
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(OpenALSoft)

#- GOOGLETEST ---------------------------------------------------------------

message("Fetching Google Test")

FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(GoogleTest)

#- JOLT PHYSICS -------------------------------------------------------------

message("Fetching Jolt Physics")

FetchContent_Declare(
    JoltPhysics
    GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
    GIT_TAG        v5.3.0
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
    SOURCE_SUBDIR "Build"
)

FetchContent_MakeAvailable(JoltPhysics)
