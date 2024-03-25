cmake_minimum_required(VERSION 3.26)

set(project column)
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        column.cpp)

set(${project}_HEADERS
        column.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
