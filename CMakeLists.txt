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
    src
    resources
)

include_directories (libplugin)
link_directories(${CMAKE_SOURCE_DIR}/libplugin)

file(GLOB SOURCE src/* )


if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else()
    add_executable(${executable_name} ${SOURCE}
        src/emulator/flightemulator.h                       src/emulator/flightemulator.cpp
        src/emulator/udpemulator.h                          src/emulator/udpemulator.cpp
        src/emulator/saroutputconsoleemulator.h             src/emulator/saroutputconsoleemulator.cpp
        src/map/tilesmanager.h                              src/map/tilesmanager.cpp
        src/map/linkerqml.h                                 src/map/linkerqml.cpp
        src/map/backend/fmousekeyhandler.h                  src/map/backend/fmousekeyhandler.cpp
        src/map/backend/scalegridbackend.h                  src/map/backend/scalegridbackend.cpp
        src/map/backend/recallhandler.h                     src/map/backend/recallhandler.cpp
        src/map/backend/flightprediction.h                  src/map/backend/flightprediction.cpp
        src/map/backend/signallinker.h                      src/map/backend/signallinker.cpp
        src/map/models/tmarker.h                            src/map/models/tmarker.cpp
        src/map/models/timage.h                             src/map/models/timage.cpp
        src/map/global/markermanager.h                      src/map/global/markermanager.cpp
        src/network/remote.h                                src/network/remote.cpp
        src/network/udpremote.h                             src/network/udpremote.cpp
        src/network/tcpdownloader.h                         src/network/tcpdownloader.cpp
        src/network/messageparser.h                         src/network/messageparser.cpp
        src/coreui.h                                        src/coreui.cpp
        src/config/config.h                                 src/config/config.cpp
        src/config/sconfig.h                                src/config/sconfig.cpp
        src/config/settingsdialog.h                         src/config/settingsdialog.cpp                                  src/config/settingsdialog.ui
        src/config/runtimedata.h                            src/config/runtimedata.cpp
        src/disk/cachemanager.h                             src/disk/cachemanager.cpp
        src/disk/disktools.h                                src/disk/disktools.cpp
        src/disk/savethread.h                               src/disk/savethread.cpp
        src/image-processing/imagemanager.h                 src/image-processing/imagemanager.cpp
        src/func/smath.h                                    src/func/smath.cpp
        src/func/stext.h                                    src/func/stext.cpp
        src/func/schecksum.h                                src/func/schecksum.cpp
        src/misc/debug.h                                    src/misc/debug.cpp
        src/misc/profiler.h                                 src/misc/profiler.cpp
        src/gui/dynamicresolution.h                         src/gui/dynamicresolution.cpp
        src/gui/passworddialog.h                            src/gui/passworddialog.cpp                                     src/gui/passworddialog.ui
        src/gui/markerdialog.h                              src/gui/markerdialog.cpp                                       src/gui/markerdialog.ui
        src/gui/applicationheader.h                         src/gui/applicationheader.cpp
        src/gui/thememanager.h                              src/gui/thememanager.cpp
        src/gui/themes/dark.h                               src/gui/themes/dark.cpp
        src/gui/themes/swampgreen.h                         src/gui/themes/swampgreen.cpp
        src/gui/widgets/colorpicker.h                       src/gui/widgets/colorpicker.cpp
        src/gui/windows/dialogwindowbackend.h               src/gui/windows/dialogwindowbackend.cpp
        src/qml.qrc
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
