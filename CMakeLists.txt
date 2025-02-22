set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(XandO VERSION 0.1.2 LANGUAGES C CXX)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/LayoutManaging/*.cpp ${CMAKE_SOURCE_DIR}/src/SceneManaging/*.cpp ${CMAKE_SOURCE_DIR}/src/UI/*.cpp) 
file(GLOB SOURCES_OBJECTLIB ${CMAKE_SOURCE_DIR}/sgl-objectlib-sample/*.cpp)
# Create shared library
add_library(sgl SHARED ${SOURCES})
add_library(sgl-objectlib-sample SHARED ${SOURCES_OBJECTLIB})
add_library(glad SHARED ${CMAKE_SOURCE_DIR}/src/glad/glad.c)

# Set output directory for sgl-objectlib-sample
set_target_properties(sgl-objectlib-sample PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/engine/libraries")

# Create executable
add_executable(XandO main.cpp)

# Link libraries
target_link_libraries(sgl glfw OpenGL::GL glad)
target_link_libraries(sgl-objectlib-sample glfw OpenGL::GL glad)
target_link_libraries(XandO sgl)

# Set installation prefix
set(CMAKE_INSTALL_PREFIX ".")

# Install targets
install(TARGETS sgl DESTINATION lib)

# Install header files
file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/SGL)

# Copy engine and scenes folders from root project dir to build dir
file(COPY ${CMAKE_SOURCE_DIR}/engine DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/scenes DESTINATION ${CMAKE_BINARY_DIR})

