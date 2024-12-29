cmake_minimum_required(VERSION 3.10)

# Project name and version
project(XandO VERSION 0.1.0 LANGUAGES C CXX)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)
<<<<<<< HEAD
<<<<<<< HEAD

# Gather source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# Create shared library
add_library(sgl SHARED ${SOURCES})

# Create executable
add_executable(XandO main.cpp)

# Link libraries
target_link_libraries(XandO glfw OpenGL::GL sgl)

# Set installation prefix
set(CMAKE_INSTALL_PREFIX ".")

# Install targets
install(TARGETS sgl DESTINATION lib)

# Install header files
file(GLOB files "${CMAKE_SOURCE_DIR}/include/*.h")
install(FILES ${files} DESTINATION include/sgl)
=======
=======

# Gather source files
>>>>>>> a73695d (Cmake update/jenikins file update)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

# Create shared library
add_library(sgl SHARED ${SOURCES})

# Create executable
add_executable(XandO main.cpp)
<<<<<<< HEAD
target_link_libraries(XandO glfw OpenGL::GL)
target_link_libraries(XandO sgl)
SET(CMAKE_INSTALL_PREFIX ".")
INSTALL(TARGETS sgl DESTINATION lib)
FILE(GLOB files "${CMAKE_SOURCE_DIR}/include/*.h")
INSTALL(FILES ${files} DESTINATION include/sgl)
>>>>>>> be5065e (BIG UPDATE,docs jenkinsfiel cmakefile)
=======

# Link libraries
target_link_libraries(XandO glfw OpenGL::GL sgl)

# Set installation prefix
set(CMAKE_INSTALL_PREFIX ".")

# Install targets
install(TARGETS sgl DESTINATION lib)

# Install header files
file(GLOB files "${CMAKE_SOURCE_DIR}/include/*.h")
install(FILES ${files} DESTINATION include/sgl)
>>>>>>> a73695d (Cmake update/jenikins file update)
