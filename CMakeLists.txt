cmake_minimum_required(VERSION 3.16.0)
project(BlizzardDiskMark VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Gui Widgets)
qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(src/app)