cmake_minimum_required(VERSION 3.10)
project(sgl VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
find_package(OpenGL REQUIRED)

# ----------------------------------------------------------
# GLFW
# ----------------------------------------------------------
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "GLFW not found, fetching via FetchContent...")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
    )
    FetchContent_MakeAvailable(glfw)
endif()

# ----------------------------------------------------------
# GLM (header-only)
# ----------------------------------------------------------
find_package(glm QUIET)
if(NOT glm_FOUND)
    message(STATUS "GLM not found, fetching via FetchContent...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

# ----------------------------------------------------------
# STB Image (header-only)
# ----------------------------------------------------------
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(stb)
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

# ----------------------------------------------------------
# FreeType2
# ----------------------------------------------------------
find_package(Freetype QUIET)
if(NOT Freetype_FOUND)
    message(STATUS "FreeType2 not found, fetching via FetchContent...")
    FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
        GIT_TAG        VER-2-14-1
    )
    FetchContent_MakeAvailable(freetype)
endif()

# ----------------------------------------------------------
# GLAD
# ----------------------------------------------------------
add_library(glad src/glad/glad.c)
target_include_directories(glad PUBLIC include)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ----------------------------------------------------------
# SGL shared library
# ----------------------------------------------------------
file(GLOB_RECURSE SGL_SOURCES "${CMAKE_SOURCE_DIR}/src/sgl/*.cpp")
file(GLOB_RECURSE SGL_ENGINE_SOURCES "${CMAKE_SOURCE_DIR}/src/sgl/engine/*.cpp")
add_library(sgl SHARED ${SGL_SOURCES} ${SGL_ENGINE_SOURCES})

target_link_libraries(sgl PUBLIC
    glfw
    glm::glm
    glad
    stb_image
    OpenGL::GL
    Freetype::Freetype
)
target_include_directories(sgl PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(sgl PUBLIC
    ${VULKAN_INCLUDE_DIRS}
)

# ----------------------------------------------------------
# Main executable
# ----------------------------------------------------------
add_executable(main main.cpp)
target_link_libraries(main PRIVATE
    sgl
)
# ----------------------------------------------------------
# Copy engine resources after build
# ----------------------------------------------------------
add_custom_command(TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory
    "$<TARGET_FILE_DIR:main>/engine"
)
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/engine"
    "$<TARGET_FILE_DIR:main>/engine"
)
