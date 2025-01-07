cmake_minimum_required(VERSION 3.15)

project(quasar-software
  VERSION 3.0.0
  DESCRIPTION "SAR control software"
  HOMEPAGE_URL "github.com/whs31/quasar-software"
  LANGUAGES C CXX
)

set(PROJECT_NAMESPACE "${PROJECT_NAME}::")
set(PROJECT_FULL_NAME "quasar::software")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# <-- msvc-related options -->
if("${CMAKE_GENERATOR}" MATCHES "^Visual Studio")
  set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)
endif()

if(MSVC)
  message(STATUS "[${PROJECT_FULL_NAME}] setting /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# <-- rc files -->
message(STATUS "[${PROJECT_FULL_NAME}] generating meta files")
if (WIN32)
  set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.ico)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/windows_metafile.rc.in "windows_metafile.rc")
  set(RES_FILES "windows_metafile.rc")
  set(CMAKE_RC_COMPILER_INIT windres)
  enable_language(RC)
  set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
  set(OUTPUT_SET ${RES_FILES})
endif ()

# <-- dependencies -->
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt5 REQUIRED COMPONENTS
  Core
  Quick
  Widgets
  Network
  Location
  Positioning
  QuickControls2
  Concurrent
)

# <-- examples -->
if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/plugins)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/plugins)
endif ()

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
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

target_sources(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCES}
    ${CPP_SOURCES}
)

# CMake options for children libraries
set(ARGPARSE_SHARED OFF CACHE BOOL "Build shared library")
set(ARGPARSE_STATIC ON CACHE BOOL "Build static library")

# Libraries and subprojects
add_subdirectory(libs/Argparse)
add_subdirectory(src/c++/sdk) # deprecated
add_subdirectory(libs/LPVL)
add_subdirectory(libs/CCL)
add_subdirectory(libs/libquasarsdk)
#add_subdirectory(libs/Corrosion) # requires rustc package
add_subdirectory(services/UpdateService)

# Linking
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  Qt5::Quick
  Qt5::Widgets
  Qt5::Network
  Qt5::Location
  Qt5::Positioning
  Qt5::QuickControls2
  Qt5::Concurrent
  #Corrosion
  argparse
  SDK
  LPVL
  CCL
  libquasarsdk
)

set(QT_VERSION ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH})
message(STATUS "[${PROJECT_FULL_NAME}] Qt version: ${QT_VERSION}")

if (WIN32 AND ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU|Clang|Mingw|MINGW" AND NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message(STATUS "[${PROJECT_FULL_NAME}] adding -mwindows linker opt (${CMAKE_CXX_COMPILER_ID}) ")
  target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
endif ()

if (WIN32)
  if (MSVC)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
  endif ()

  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS
  )
endif ()

if (NOT WIN32)
  message(STATUS "[${PROJECT_FULL_NAME}] copying ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json to the root folder ${CMAKE_CURRENT_SOURCE_DIR}")
  file(CREATE_LINK
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    SYMBOLIC
  )
endif ()

# <-- vendor -->
message(STATUS "[${PROJECT_FULL_NAME}] preparing vendored libraries")
if (WIN32)
  if (MSVC)
    set(VENDOR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/win32/msvc")
    message(STATUS "[${PROJECT_FULL_NAME}] target: ${VENDOR_SOURCE_DIR}")
    file(GLOB VENDOR_DLLS "${VENDOR_SOURCE_DIR}/*.dll" "${VENDOR_SOURCE_DIR}/*.so" "${VENDOR_SOURCE_DIR}/*.dylib")
    foreach (DLL ${VENDOR_DLLS})
      add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "copying ${DLL} to $<TARGET_FILE_DIR:${PROJECT_NAME}>"
      )
    endforeach ()
  else ()
  endif ()
else ()
endif ()


