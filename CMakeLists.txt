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

include_directories(
    network
    src
    misc
    config
    image-processing
    map
    json
    func
    gui
    disk
    emulator
    resources
)

include_directories (libplugin)
link_directories(${CMAKE_SOURCE_DIR}/libplugin)

file(GLOB SOURCE src/* )


if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else()
    add_executable(${executable_name} ${SOURCE}
        emulator/flightemulator.h                           emulator/flightemulator.cpp
        emulator/udpemulator.h                              emulator/udpemulator.cpp
        emulator/saroutputconsoleemulator.h                 emulator/saroutputconsoleemulator.cpp
        map/tilesmanager.h                                  map/tilesmanager.cpp
        map/linkerqml.h                                     map/linkerqml.cpp
        map/backend/fmousekeyhandler.h                      map/backend/fmousekeyhandler.cpp
        map/backend/scalegridbackend.h                      map/backend/scalegridbackend.cpp
        map/backend/recallhandler.h                         map/backend/recallhandler.cpp
        map/backend/flightprediction.h                      map/backend/flightprediction.cpp
        map/backend/signallinker.h                          map/backend/signallinker.cpp
        map/models/tmarker.h                                map/models/tmarker.cpp
        map/models/timage.h                                 map/models/timage.cpp
        map/global/markermanager.h                          map/global/markermanager.cpp
        json/jsonmanager.h                                  json/jsonmanager.cpp
        json/jsonconfig.h                                   json/jsonconfig.cpp
        network/remote.h                                    network/remote.cpp
        network/udpremote.h                                 network/udpremote.cpp
        network/tcpdownloader.h                             network/tcpdownloader.cpp
        network/messageparser.h                             network/messageparser.cpp
        src/coreui.h                                        src/coreui.cpp
        config/config.h                                     config/config.cpp
        config/sconfig.h                                    config/sconfig.cpp
        config/settingsdialog.h                             config/settingsdialog.cpp                                      config/settingsdialog.ui
        config/runtimedata.h                                config/runtimedata.cpp
        disk/cachemanager.h                                 disk/cachemanager.cpp
        disk/disktools.h                                    disk/disktools.cpp
        disk/savethread.h                                   disk/savethread.cpp
        image-processing/imagemanager.h                     image-processing/imagemanager.cpp
        func/smath.h                                        func/smath.cpp
        func/stext.h                                        func/stext.cpp
        func/schecksum.h                                    func/schecksum.cpp
        misc/style.h                                        misc/style.cpp
        misc/uxmanager.h                                    misc/uxmanager.cpp
        misc/debug.h                                        misc/debug.cpp
        misc/profiler.h                                     misc/profiler.cpp
        misc/json-backup.qrc                                src/map-resources.qrc                                          src/qml.qrc
        gui/dynamicresolution.h                             gui/dynamicresolution.cpp
        gui/passworddialog.h                                gui/passworddialog.cpp                                         gui/passworddialog.ui
        gui/markerdialog.h                                  gui/markerdialog.cpp                                           gui/markerdialog.ui
        gui/applicationheader.h                             gui/applicationheader.cpp
        gui/thememanager.h                                  gui/thememanager.cpp
        gui/themes/dark.h                                   gui/themes/dark.cpp
        gui/themes/swampgreen.h                             gui/themes/swampgreen.cpp
        gui/widgets/colorpicker.h                           gui/widgets/colorpicker.cpp
        src/fonts.qrc                                       src/vector-resources.qrc
        src/buildprefs.h
        resources/resources.qrc

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
    target_link_libraries(${executable_name}
        plugin
    )
endif()

if((( ( UNIX ) AND NOT APPLE ) AND NOT ANDROID) AND ((QT_VERSION_MAJOR EQUAL 5)))
    target_link_libraries(${executable_name}
        Qt::Test
        plugin
    )
endif()

execute_process(COMMAND git remote update WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND git describe --tags --always WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(-DPROJECT_NAME="${PROJECT_NAME}" -DPROJECT_VERSION="${GIT_VERSION}")
string(TIMESTAMP PROJECT_BUILD_DATE "%d.%m.%Y %H:%M:%S" UTC)
