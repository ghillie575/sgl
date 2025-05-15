set(CMAKE_INSTALL_RPATH "$ORIGIN")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
cmake_minimum_required(VERSION 3.10)
include(FetchContent)
# Project name and version
project(XandO VERSION 0.1.2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(PNG REQUIRED)
find_package(HarfBuzz QUIET)
if (NOT TARGET HarfBuzz::HarfBuzz)
    add_library(HarfBuzz::HarfBuzz UNKNOWN IMPORTED)
    set_target_properties(HarfBuzz::HarfBuzz PROPERTIES
        IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libharfbuzz.so"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/include/harfbuzz"
    )
endif()
find_package(freetype REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/usr/local/include/freetype2)
include_directories(/usr/local/include/PhysX)
link_directories(/usr/local/lib)

# Gather source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/LayoutManaging/*.cpp ${CMAKE_SOURCE_DIR}/src/SceneManaging/*.cpp ${CMAKE_SOURCE_DIR}/src/UI/*.cpp)
file(GLOB SOURCES_OBJECTLIB ${CMAKE_SOURCE_DIR}/sgl-objectlib-sample/*.cpp)

# Create shared library
add_library(sgl SHARED ${SOURCES})
add_library(sgl-objectlib-sample SHARED ${SOURCES_OBJECTLIB})
add_library(glad SHARED ${CMAKE_SOURCE_DIR}/src/glad/glad.c)

# Set output directories

# Create executable
add_executable(XandO main.cpp)

# Link libraries
target_link_libraries(sgl glfw OpenGL::GL glad freetype)
target_link_libraries(sgl-objectlib-sample glfw OpenGL::GL glad)

target_link_libraries(sgl
    PhysX_static_64
    PhysXCommon_static_64
    PhysXFoundation_static_64
    PhysXExtensions_static_64
    PhysXCooking_static_64
)
target_link_libraries(XandO
    PhysX_static_64
    PhysXCommon_static_64
    PhysXFoundation_static_64
    PhysXExtensions_static_64
    PhysXCooking_static_64
)


target_link_libraries(XandO sgl)

# Set installation prefix
set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS sgl glad XandO
    RUNTIME DESTINATION .
    LIBRARY DESTINATION .
)
install(TARGETS sgl-objectlib-sample
    LIBRARY DESTINATION engine/libraries
)
file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/include/SGL/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/SGL)

install(FILES /usr/lib/x86_64-linux-gnu/libglfw.so DESTINATION .)
# Copy engine and scenes folders from root project dir to build dir
file(COPY ${CMAKE_SOURCE_DIR}/engine DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/scenes DESTINATION ${CMAKE_BINARY_DIR})
