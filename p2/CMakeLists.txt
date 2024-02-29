cmake_minimum_required(VERSION 3.10)
project(p2)

#set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")

#include the directory containing raylib headers
#include_directories(${RAYLIB_DIR}/include)

#add the path to raylib library
#link_directories(${RAYLIB_DIR}/lib)

#create executable
add_executable(p2 src/main.cpp)
target_link_libraries(p2 PUBLIC raylib raylib_cpp)
set_property(TARGET p2 PROPERTY CXX_STANDARD 20)

#link raylib library
#target_link_libraries(p2 raylib)