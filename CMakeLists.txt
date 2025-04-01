cmake_minimum_required(VERSION 3.16.0)
project(BlizzardDiskMark VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick Gui Widgets)
qt_standard_project_setup(REQUIRES 6.8)

qt_policy(SET QTP0004 NEW)
set(CMAKE_AUTOMOC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

add_subdirectory(src/app)
add_subdirectory(src/Igloo)