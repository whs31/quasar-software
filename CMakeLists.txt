cmake_minimum_required(VERSION 3.13)

project(QuaSAR-UI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core )
find_package(Qt5 COMPONENTS Gui Widgets QuickWidgets REQUIRED Network Location Positioning)
find_package(Qt5 REQUIRED COMPONENTS QuickControls2)

include_directories(
    network
    src
    src/resources
    misc
    config
    image-processing
)


#link_directories(lib)

file(GLOB SOURCE src/* )
file(GLOB RES src/resources/*)

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else()
    add_executable(${PROJECT_NAME} ${SOURCE}
        network/remote.h
        network/tcpremote.h
        network/udpremote.h
        network/tcpdownloader.h
        network/tcpremote.cpp
        network/udpremote.cpp
        network/remote.cpp
        network/tcpdownloader.cpp
        network/messageparser.h
        network/messageparser.cpp
        src/coreui.h
        src/linkerqml.h
        src/coreui.cpp
        src/coreui-guislots.cpp
        src/linkerqml.cpp
        config/config.h
        config/settingsdialog.h
        config/sconfig.h
        config/config.cpp
        config/settingsdialog.cpp
        config/settingsdialog.ui
        config/sconfig.cpp
        image-processing/imageprocessing.h
        image-processing/imagemanager.h
        image-processing/imageprocessing.cpp
        image-processing/imagemanager.cpp
        misc/style.h
        misc/uxmanager.h
        misc/debug.h
        misc/style.cpp
        misc/uxmanager.cpp
        misc/debug.cpp
   )
endif()

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
