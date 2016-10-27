cmake_minimum_required(VERSION 2.6)
project(device)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

add_executable(device main.cpp)

install(TARGETS device RUNTIME DESTINATION bin)
