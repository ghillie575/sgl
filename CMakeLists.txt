cmake_minimum_required(VERSION 3.10)
project(XandO VERSION 0.1.0 LANGUAGES C CXX)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
add_executable(XandO main.cpp ${SOURCES})
target_include_directories(XandO PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(XandO glfw OpenGL::GL)
message(STATUS "Copying engine files")
execute_process(
    COMMAND ${CMAKE_COMMAND} -E remove_directory ./engine
    COMMAND ${CMAKE_COMMAND} -E copy_directory ../engine ./engine
)