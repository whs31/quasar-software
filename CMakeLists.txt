cmake_minimum_required(VERSION 3.15)

project(QuaSAR LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake)
include(qtprojectbuild)

project_version_patch_clean()

set(COMPANY "Radar-MMS")
set(COPYRIGHT "Copyright (c) 2023 ${COMPANY}. All rights reserved.")
set(IDENTIFIER "${PROJECT_NAME}")

add_project_meta(META_FILES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    Network
    Location
    Positioning
    QuickControls2
    Concurrent
    Quick3D
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
)

set(PROJECT_SOURCES
    src/cpp/main.c++
    src/cpp/entry.h    src/cpp/entry.c++

    src/qml/qml.qrc
    resources/resources.qrc
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CPP_SOURCES}
    ${META_FILES}
)

add_subdirectory(libs/LVPL)
add_subdirectory(libs/quasar-emulator)

if(WIN32)
    set_property(TARGET LPVL PROPERTY IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/libs/LVPL/build/liblpvl.dll.a")
    set_property(TARGET LPVL PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/LVPL/build/lpvl.dll")
else()
    set_property(TARGET LPVL PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/LVPL/build/lpvl.so")
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Location
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Quick3D
    LPVL
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_definitions(
    -DPROJECT_NAME="${PROJECT_NAME}"
    -DPROJECT_VERSION="${PROJECT_VERSION}"
    -DPROJECT_COMPANY="${COMPANY}"
)

message("${PROJECT_NAME} version ${PROJECT_VERSION} compiled successfully")

