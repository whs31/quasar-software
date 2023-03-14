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

include_directories(
    src
    resources
)

include_directories (libplugin)
link_directories(${CMAKE_SOURCE_DIR}/libplugin)

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SOURCE})
else()
    add_executable(${executable_name} ${SOURCE}
        src/main.cpp
        #src/buildprefs.h                                                                                       -removed
        src/macro.h
        src/coreui.h                                    src/coreui.cpp                                      src/coreui.ui
        src/data/datatelemetry.h                        src/data/datatelemetry.cpp
        src/data/datasar.h                              src/data/datasar.cpp
        src/data/dataformparameters.h                   src/data/dataformparameters.cpp
        src/emulator/flightemulator.h                   src/emulator/flightemulator.cpp                     #marked as deprecated, to be reworked soon
        src/emulator/udpemulator.h                      src/emulator/udpemulator.cpp                        #marked as deprecated, to be reworked soon
        src/emulator/saroutputconsoleemulator.h         src/emulator/saroutputconsoleemulator.cpp           #marked as deprecated, to be reworked soon
        src/map/tilesmanager.h                          src/map/tilesmanager.cpp                            #marked as deprecated, to be reworked soon
        src/map/linkerqml.h                             src/map/linkerqml.cpp                               #marked as deprecated, to be reworked soon
        src/map/backend/fmousekeyhandler.h              src/map/backend/fmousekeyhandler.cpp                #marked as deprecated, to be reworked soon
        src/map/backend/scalegridbackend.h              src/map/backend/scalegridbackend.cpp                #planned to rework
        src/map/backend/recallhandler.h                 src/map/backend/recallhandler.cpp                   #marked as deprecated, can be splitted into 3 methods
        src/map/backend/flightprediction.h              src/map/backend/flightprediction.cpp
        src/map/backend/signallinker.h                  src/map/backend/signallinker.cpp                    #marked as deprecated, to be reworked soon
        src/map/models/marker.h                         src/map/models/marker.cpp
        src/map/models/image.h                          src/map/models/image.cpp
        src/map/global/markermanager.h                  src/map/global/markermanager.cpp
        src/network/modules/abstract/remote.h           src/network/modules/abstract/remote.cpp
        src/network/udpremote.h                         src/network/udpremote.cpp
        src/network/tcpdownloader.h                     src/network/tcpdownloader.cpp
        src/network/modules/telemetryremote.h           src/network/modules/telemetryremote.cpp
        src/network/modules/execdremote.h               src/network/modules/execdremote.cpp
        src/network/modules/feedbackremote.h            src/network/modules/feedbackremote.cpp
        src/network/modules/execd/argumentlist.h        src/network/modules/execd/argumentlist.cpp
        src/network/modules/execd/execdargument.h       src/network/modules/execd/execdargument.cpp
        src/config/config.h                             src/config/config.cpp
        src/config/sconfig.h                            src/config/sconfig.cpp                              #marked as deprecated, to be reworked soon
        src/config/settingsdialog.h                     src/config/settingsdialog.cpp                       src/config/settingsdialog.ui
        src/config/runtimedata.h                        src/config/runtimedata.cpp
        src/disk/cachemanager.h                         src/disk/cachemanager.cpp                           #marked as deprecated, to be reworked soon
        src/disk/disktools.h                            src/disk/disktools.cpp                              #marked as deprecated, to be reworked soon
        src/disk/savethread.h                           src/disk/savethread.cpp                             #marked as deprecated, to be reworked soon
        src/image-processing/imagemanager.h             src/image-processing/imagemanager.cpp
        src/func/smath.h                                src/func/smath.cpp
        src/func/stext.h                                src/func/stext.cpp
        src/func/schecksum.h                            src/func/schecksum.cpp
        #src/gui/dynamicresolution.h                     src/gui/dynamicresolution.cpp                          -removed
        src/gui/passworddialog.h                        src/gui/passworddialog.cpp                          src/gui/passworddialog.ui
        src/gui/applicationheader.h                     src/gui/applicationheader.cpp
        #src/gui/thememanager.h                          src/gui/thememanager.cpp                               -removed
        #src/gui/themes/dark.h                           src/gui/themes/dark.cpp                                -removed
        #src/gui/themes/swampgreen.h                     src/gui/themes/swampgreen.cpp                          -removed
	#src/gui/widgets/colorpicker.h                   src/gui/widgets/colorpicker.cpp			-removed
        src/gui/windows/abstract/windowbackend.h        src/gui/windows/abstract/windowbackend.cpp
        src/gui/windows/dialogwindowbackend.h           src/gui/windows/dialogwindowbackend.cpp
        src/gui/windows/markerwindowbackend.h           src/gui/windows/markerwindowbackend.cpp
        src/gui/windows/autocapturemarkwindowbackend.h  src/gui/windows/autocapturemarkwindowbackend.cpp
        src/gui/windows/settingswindowbackend.h         src/gui/windows/settingswindowbackend.cpp
        src/gui/windows/focuswindowbackend.h            src/gui/windows/focuswindowbackend.cpp              #planned to rework

	# new modules (after refork)
	src/theme/include/theme.hpp			src/theme/src/theme.cpp					src/theme/src/theme_p.hpp
        src/map/backend/routelogger.h                   src/map/backend/routelogger.cpp
        src/network/tcpdebug.h                          src/network/tcpdebug.cpp                                src/network/tcpdebug.ui

        src/qml.qrc
        src/qss.qrc
        src/osmconfig.qrc
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
