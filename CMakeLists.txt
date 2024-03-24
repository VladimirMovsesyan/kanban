cmake_minimum_required(VERSION 3.26)

set(project kanban)
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main.cpp)

find_package(SFML COMPONENTS graphics audio REQUIRED)

set(SFML_INCLUDE_DIRS /opt/homebrew/include/)
set(SFML_LIBRARIES /opt/homebrew/lib/libsfml-audio.dylib
        /opt/homebrew/lib/libsfml-graphics.dylib
        /opt/homebrew/lib/libsfml-network.dylib
        /opt/homebrew/lib/libsfml-system.dylib
        /opt/homebrew/lib/libsfml-window.dylib)

include_directories(${SFML_INCLUDE_DIRS})
set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} ${SFML_LIBRARIES})