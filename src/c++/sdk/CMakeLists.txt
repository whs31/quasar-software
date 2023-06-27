cmake_minimum_required (VERSION 3.15)

project(SDK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    Positioning
)

include_directories(src include)

set(SDK_CORE
    src/cartography/sdkgeomath.h src/cartography/sdkgeomath.c++
    src/cartography/sdkorthodrom.h src/cartography/sdkorthodrom.c++
)

set(SDK_CORE_INCLUDE
    include/SDK/GeoMath
    include/SDK/Orthodrom
)

set(SRC ${SDK_CORE} ${SDK_CORE_INCLUDE} )

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Positioning
)

target_include_directories(${PROJECT_NAME} PUBLIC include src)
