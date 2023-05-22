cmake_minimum_required(VERSION 3.15)

project(QuaSAR LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    Network
    Location
    Positioning
    QuickControls2
    Concurrent
)

include_directories(src/cpp libs)

file(GLOB_RECURSE CPP_SOURCES
    src/cpp/gui/*
    src/cpp/filesystem/*
    src/cpp/config/*
    src/cpp/map/*
    src/cpp/scenegraph/*
    src/cpp/network/*
    src/cpp/processing/*

    libs/ccl/*
)

set(PROJECT_SOURCES
    src/cpp/main.c++
    src/cpp/entry.h    src/cpp/entry.c++

    src/qml/qml.qrc
    resources/resources.qrc
    ${SRCS} resources/ico.rc
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CPP_SOURCES}
)

add_library(CCL SHARED IMPORTED)
add_subdirectory(libs/lpvl)
if(WIN32)
    set_property(TARGET CCL PROPERTY IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/libs/ccl/imp/libccl.dll.a")
    set_property(TARGET CCL PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/ccl/shared/libccl.dll")

    set_property(TARGET LPVL PROPERTY IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/libs/lpvl/build/liblpvl.dll.a")
    set_property(TARGET LPVL PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/lpvl/build/lpvl.dll")
else()
    set_property(TARGET CCL PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/lpvl/build/libccl.so")
    set_property(TARGET LPVL PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/lpvl/build/lpvl.so")
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Location
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Concurrent
    CCL
    LPVL
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

message("QuaSAR compiled successfully")
execute_process(COMMAND git remote update WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND git describe --tags --always WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}" -DPROJECT_VERSION="${GIT_VERSION}")
string(TIMESTAMP PROJECT_BUILD_DATE "%d.%m.%Y %H:%M:%S" UTC)
