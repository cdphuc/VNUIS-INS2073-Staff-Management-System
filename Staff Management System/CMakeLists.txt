cmake_minimum_required(VERSION 3.28)
project(Staff_Management_System)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(SOURCE_FILE main.cpp)
add_executable(Staff_Management_System main.cpp)
