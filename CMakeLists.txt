cmake_minimum_required(VERSION 3.13)

project(QuaSAR-UI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core )
find_package(Qt5 COMPONENTS Gui Widgets QuickWidgets REQUIRED Network Location Positioning)
find_package(Qt5 REQUIRED COMPONENTS QuickControls2)

find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

if( OPENSSL_FOUND )
    include_directories(${OPENSSL_INCLUDE_DIRS})
    message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
else()
    # Error; with REQUIRED, pkg_search_module() will throw an error by it's own
endif()

include_directories(
    network
    src
    config
    image-processing
)


#link_directories(lib)

file(GLOB SOURCE src/* )
file(GLOB NETWORK network/*)
file(GLOB CONFIG config/*)
file(GLOB CONFIG image-processing/*)

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else()
    add_executable(${PROJECT_NAME} ${SOURCE}
        network/remote.h
        network/tcpremote.h
        network/udpremote.h
        network/tcpremote.cpp
        network/udpremote.cpp
        network/remote.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        config/config.h
        config/confighandler.h
        config/settingsdialog.h
        config/config.cpp
        config/confighandler.cpp
        config/settingsdialog.cpp
        config/settingsdialog.ui
        image-processing/imageprocessing.h
        image-processing/imageprocessing.cpp
   )
endif()

find_package(OpenSSL REQUIRED)
if( OpenSSL_FOUND )
   include_directories(${OPENSSL_INCLUDE_DIRS})
   link_directories(${OPENSSL_LIBRARIES})
   message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif()
#target_link_libraries(${PROJECT_NAME} /path/of/libssl.so /path/of/libcrypto.so)

target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Location
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt5::QuickControls2
)


add_subdirectory(submodule)

execute_process(COMMAND git describe --tags --always WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CMAKE_COMMAND} -E env TZ=UTC git log -1 --format=%cd --date=format-local:"%d.%m.%Y %H:%M:%S" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_SOURCE_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TIMESTAMP PROJECT_BUILD_DATE "%d.%m.%Y %H:%M:%S" UTC)
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}" -DPROJECT_VERSION="${GIT_VERSION}" -DPROJECT_SOURCE_DATE=${GIT_SOURCE_DATE} -DPROJECT_BUILD_DATE="${PROJECT_BUILD_DATE}")
