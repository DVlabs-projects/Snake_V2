cmake_minimum_required(VERSION 3.14)
project(Snake
    VERSION 1.0.0
    DESCRIPTION "Snake Game"
    LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES 
    "src/*.h"
    "src/*.cpp"
)

add_executable(snake WIN32 
    ${SOURCES}
    resources.qrc
)

target_link_libraries(snake PRIVATE
    Qt5::Core
    Qt5::Widgets)

set_property(TARGET snake PROPERTY WIN32_EXECUTABLE TRUE)