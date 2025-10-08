cmake_minimum_required(VERSION 3.10)
project(sgl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionally set where bgfx should install (if you want to install it)
# set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/thirdparty-install)

# Include the bgfx.cmake project
add_subdirectory(external/bgfx.cmake)

# Now, targets bgfx, bx, bimg are available

# Find GLFW from system packages
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Your include dirs
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GLFW_INCLUDE_DIRS}
)

# SGL static library
file(GLOB_RECURSE SGL_SOURCES "${CMAKE_SOURCE_DIR}/src/sgl/*.cpp")

add_library(sgl SHARED ${SGL_SOURCES})
target_include_directories(sgl PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${GLFW_INCLUDE_DIRS}
)

# Link to bx, bimg, bgfx
target_link_libraries(sgl PUBLIC
    bx
    bimg
    bgfx
)

# Main executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE sgl ${GLFW_LIBRARIES})
