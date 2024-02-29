cmake_minimum_required(VERSION 3.10)
project(p3)

#set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")

#include the directory containing raylib headers
#include_directories(${RAYLIB_DIR}/include)

#add the path to raylib library
#link_directories(${RAYLIB_DIR}/lib)

#create executable
add_executable(p3 src/main.cpp)
target_link_libraries(p3 PUBLIC raylib raylib_cpp)
set_property(TARGET p3 PROPERTY CXX_STANDARD 20)
# Link raylib library
#target_link_libraries(p3 raylib)

#define source and destination paths for meshes
set(TEXTURES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/textures)
set(TEXTURES_DEST_DIR ${CMAKE_BINARY_DIR}/textures)

#copy meshes to build directory during build
file(COPY ${TEXTURES_SOURCE_DIR} DESTINATION ${TEXTURES_DEST_DIR})