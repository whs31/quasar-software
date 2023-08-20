cmake_minimum_required(VERSION 3.15)

project(QuaSAR LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake)
include(qtprojectbuild)

project_version_patch_clean()

set(COMPANY "Radar-MMS")
set(COPYRIGHT "Copyright (c) 2023 ${COMPANY}. All rights reserved.")
set(IDENTIFIER "${PROJECT_NAME}")

add_project_meta(META_FILES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3rd party packages locating
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
  Core
  Quick
  Widgets
  Network
  Location
  Positioning
  QuickControls2
  Concurrent
  )

include_directories(src/c++ libs)

# Source including
file(GLOB_RECURSE CPP_SOURCES
  src/c++/application/*
  src/c++/gui/*
  src/c++/filesystem/*
  src/c++/config/*
  src/c++/map/*
  src/c++/scenegraph/*
  src/c++/network/*
  src/c++/processing/*
  )

set(PROJECT_SOURCES
  src/c++/main.c++
  src/c++/quasar.h src/c++/quasar.c++

  src/qml/qml.qrc
  src/js/js.qrc
  resources/resources.qrc
  )

# Making executable
add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${CPP_SOURCES}
  ${META_FILES}
  )

# CMake options for children libraries
set(ARGPARSE_SHARED OFF CACHE BOOL "Build shared library")
set(ARGPARSE_STATIC ON CACHE BOOL "Build static library")

# Libraries and subprojects
add_subdirectory(libs/Argparse)
add_subdirectory(src/c++/sdk) # deprecated
add_subdirectory(libs/LPVL)
add_subdirectory(libs/libquasarsdk)
#add_subdirectory(libs/Corrosion) # requires rustc package
add_subdirectory(services/UpdateService)

# Linking
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Location
  Qt${QT_VERSION_MAJOR}::Positioning
  Qt${QT_VERSION_MAJOR}::QuickControls2
  Qt${QT_VERSION_MAJOR}::Concurrent
  argparse
  SDK
  LPVL
  libquasarsdk
)

install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

# Git version fetching
execute_process(COMMAND git remote update WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND git describe --tags --abbrev=0 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)

# C++ definitions
add_definitions(
  -DPROJECT_NAME="${PROJECT_NAME}"
  -DPROJECT_VERSION="${GIT_VERSION}"
  -DPROJECT_COMPANY="${COMPANY}"
)

message("${PROJECT_NAME} version ${PROJECT_VERSION} compiled successfully")

