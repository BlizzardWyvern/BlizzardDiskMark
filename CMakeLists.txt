cmake_minimum_required(VERSION 3.21)
string(TIMESTAMP CURRENT_DATE "%y.%m.%d.0")
add_definitions(-DVERSION="${CURRENT_DATE}")
add_definitions(-DBUILDTYPE="${CMAKE_BUILD_TYPE}")
project(BlizzardDiskMark VERSION ${CURRENT_DATE} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick Gui Widgets WebView)
qt_standard_project_setup(REQUIRES 6.8)

set(WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

cmake_policy(SET CMP0156 NEW)
qt_policy(SET QTP0004 NEW)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)
set(QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/modules/BlizzardIgloo")
set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_definitions(-DARCHITECTURE="${CMAKE_VS_PLATFORM_NAME}")
add_subdirectory(src/modules/BlizzardIgloo)
add_subdirectory(src/apps/BlizzardDiskMark)