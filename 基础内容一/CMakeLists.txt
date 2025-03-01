cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(qtguide)

#cmake通过这个变量来寻找路径
set(Qt5_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

file(GLOB sources *.cpp)
add_executable(qtguide ${sources})
target_link_libraries(qtguide PRIVATE Qt5::Core Qt5::Widgets)
