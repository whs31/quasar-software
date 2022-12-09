#FIX QGOODWINDOW

cmake_minimum_required(VERSION 3.13)

project(QuaSAR-UI)
set(executable_name Quasar)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core )
find_package(Qt5 COMPONENTS Gui Widgets QuickWidgets Test REQUIRED Network Location Positioning)
find_package(Qt5 REQUIRED COMPONENTS QuickControls2)
if(WIN32)
    find_package(Qt5 OPTIONAL_COMPONENTS WinExtras)
else()
    find_package(Qt5 OPTIONAL_COMPONENTS X11Extras)
endif()

if(NOT WIN32)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
endif()


include_directories(
    network
    src
    src/resources
    misc
    config
    image-processing
    map
    json
    windowextension
    func
    gui
)

if(NOT WIN32)
    include_directories (
      ${GTK2_INCLUDE_DIRS}
      )
endif()


#link_directories(lib)

file(GLOB SOURCE src/* )
file(GLOB RES src/resources/*)



if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else()
    add_executable(${executable_name} ${SOURCE}
        windowextension/extension.h
        windowextension/extension.cpp
        windowextension/shadow.h
        windowextension/shadow.cpp
        windowextension/common.h
        map/tilesmanager.h
        map/tilesmanager.cpp
        map/linkerqml.h
        map/linkerqml.cpp
        map/backend/ftelemetry.h
        map/backend/ftelemetry.cpp
        map/backend/fdynamicvariables.h
        map/backend/fdynamicvariables.cpp
        map/backend/fstaticvariables.h
        map/backend/fstaticvariables.cpp
        map/backend/fmousekeyhandler.h
        map/backend/fmousekeyhandler.cpp
        json/jsonmanager.h
        json/jsonmanager.cpp
        json/jsonconfig.h
        json/jsonconfig.cpp
        network/remote.h
        network/remote.cpp
        network/tcpremote.h
        network/tcpremote.cpp
        network/udpremote.h
        network/udpremote.cpp
        network/tcpdownloader.h
        network/tcpdownloader.cpp
        network/messageparser.h
        network/messageparser.cpp
        src/coreui.h
        src/coreui.cpp
        src/coreui-guislots.cpp
        config/config.h
        config/config.cpp
        config/sconfig.h
        config/sconfig.cpp
        config/settingsdialog.h
        config/settingsdialog.cpp
        config/settingsdialog.ui
        image-processing/imageprocessing.h
        image-processing/imageprocessing.cpp
        image-processing/imagemanager.h
        image-processing/imagemanager.cpp
        func/smath.h
        func/smath.cpp
        func/stext.h
        func/stext.cpp
        func/schecksum.h
        func/schecksum.cpp
        misc/style.h
        misc/style.cpp
        misc/uxmanager.h
        misc/uxmanager.cpp
        misc/debug.h
        misc/debug.cpp
        misc/profiler.h
        misc/profiler.cpp
        misc/json-backup.qrc
        gui/aboutdialog.h
        gui/aboutdialog.cpp
        gui/aboutdialog.ui
        ${SRCS} appiconwin32.rc
   )
endif()


target_link_libraries(${executable_name}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Location
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt5::QuickControls2
)


if(WIN32)
    target_compile_definitions(${executable_name} PRIVATE
        QGOODWINDOW
    )

    target_link_libraries(${executable_name}
        Qt::WinExtras
        Gdi32
        User32
    )
endif()


if(UNIX AND NOT ANDROID AND NOT APPLE)
    target_compile_definitions(${executable_name} PRIVATE
        QGOODWINDOW
    )

    target_link_libraries(${executable_name}
        X11
        ${GTK2_LIBRARIES}
    )
endif()

if((( ( UNIX ) AND NOT APPLE ) AND NOT ANDROID) AND ((QT_VERSION_MAJOR EQUAL 5)))
    target_compile_definitions(${executable_name} PRIVATE
        QGOODWINDOW
    )
    target_link_libraries(${executable_name}
        Qt::Test
        Qt::X11Extras
    )
endif()

execute_process(COMMAND git describe --tags --always WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CMAKE_COMMAND} -E env TZ=UTC git log -1 --format=%cd --date=format-local:"%d.%m.%Y %H:%M:%S" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_SOURCE_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TIMESTAMP PROJECT_BUILD_DATE "%d.%m.%Y %H:%M:%S" UTC)
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}" -DPROJECT_VERSION="${GIT_VERSION}" -DPROJECT_SOURCE_DATE=${GIT_SOURCE_DATE} -DPROJECT_BUILD_DATE="${PROJECT_BUILD_DATE}")
