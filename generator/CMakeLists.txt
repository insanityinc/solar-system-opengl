cmake_minimum_required(VERSION 3.13)
project(generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(generator src/generate.cpp src/generate.h)