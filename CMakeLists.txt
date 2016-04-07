cmake_minimum_required(VERSION 3.5)
project(dplist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    dplist.c
    dplist.h
    main.c)

add_executable(dplist ${SOURCE_FILES})