cmake_minimum_required (VERSION 3.15)

project(libquasarsdk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Network
    Gui
)

include_directories(src include)

file(GLOB_RECURSE SDK_CORE src/* )
file(GLOB_RECURSE SDK_CORE_INCLUDE include/* )
set(SRC ${SDK_CORE} ${SDK_CORE_INCLUDE} )

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
   Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Gui
)

target_include_directories(${PROJECT_NAME} PUBLIC include src)
