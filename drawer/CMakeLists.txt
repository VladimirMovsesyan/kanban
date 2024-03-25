cmake_minimum_required(VERSION 3.26)

set(project drawer)
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        drawer.cpp)

set(${project}_HEADERS
        drawer.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})