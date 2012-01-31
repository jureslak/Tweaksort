cmake_minimum_required(VERSION 2.8)

project (tweaksort)

add_definitions(-O3 -Wall -Weffc++ -pedantic -std=gnu++0x)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lrt")

add_executable(test test.cpp)
add_executable(bullshit bullshit.cpp)
add_executable(learn learn.cpp)
add_executable(log log.cpp)
