QT       += core gui widgets quickwidgets network location positioning quickcontrols2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui-private

CONFIG += c++17
INCLUDEPATH = c:/Users/User/Documents/aqt/quasar-dev/quasar/libplugin
LIBS += -Lc:/Users/User/Documents/aqt/quasar-dev/quasar/libplugin -lplugin

QMAKE_LFLAGS += -Wl,--rpath=$$INCLUDEPATH

INCLUDEPATH += src/

SOURCES += \
    src/main.cpp \
    src/coreui.cpp \
    src/data/datatelemetry.cpp \
    src/data/datasar.cpp \
    src/data/dataformparameters.cpp \
    src/emulator/flightemulator.cpp \
    src/emulator/udpemulator.cpp \
    src/emulator/saroutputconsoleemulator.cpp \
    src/map/tilesmanager.cpp \
    src/map/linkerqml.cpp \
    src/map/backend/fmousekeyhandler.cpp \
    src/map/backend/scalegridbackend.cpp \
    src/map/backend/recallhandler.cpp \
    src/theme/src/theme.cpp \
    src/map/backend/routelogger.cpp \
    src/network/tcpdebug.cpp \
    src/map/backend/flightprediction.cpp \
     src/map/backend/signallinker.cpp     \
    src/map/models/marker.cpp \
     src/map/models/image.cpp \
     src/map/global/markermanager.cpp \
     src/network/modules/abstract/remote.cpp \
     src/network/udpremote.cpp \
     src/network/tcpdownloader.cpp \
     src/network/modules/telemetryremote.cpp \
     src/network/modules/execdremote.cpp \
     src/network/modules/feedbackremote.cpp \
     src/network/modules/execd/argumentlist.cpp \
     src/network/modules/execd/execdargument.cpp \
     src/config/config.cpp \
     src/config/sconfig.cpp  \
    src/config/settingsdialog.cpp  \
    src/config/runtimedata.cpp \
     src/disk/cachemanager.cpp   \
    src/disk/disktools.cpp        \
    src/disk/savethread.cpp        \
    src/image-processing/imagemanager.cpp \
     src/func/smath.cpp \
     src/func/stext.cpp \
     src/func/schecksum.cpp \
     src/gui/passworddialog.cpp  \
    src/gui/applicationheader.cpp \
     src/gui/windows/abstract/windowbackend.cpp \
     src/gui/windows/dialogwindowbackend.cpp \
     src/gui/windows/markerwindowbackend.cpp \
     src/gui/windows/autocapturemarkwindowbackend.cpp \
    src/gui/windows/settingswindowbackend.cpp \
     src/gui/windows/focuswindowbackend.cpp    \

HEADERS += \
    src/macro.h \
    src/coreui.h \
    src/data/datatelemetry.h \
    src/data/datasar.h \
    src/data/dataformparameters.h \
    src/emulator/flightemulator.h \
    src/emulator/udpemulator.h \
    src/emulator/saroutputconsoleemulator.h \
    src/map/tilesmanager.h \
    src/map/linkerqml.h \
    src/map/backend/fmousekeyhandler.h \
    src/map/backend/scalegridbackend.h \
    src/map/backend/recallhandler.h \
    src/network/tcpdebug.h \
    src/theme/include/theme.hpp \
    src/theme/src/theme_p.hpp \
    src/map/backend/routelogger.h \
    src/map/backend/flightprediction.h \
    src/map/backend/signallinker.h \
    src/map/models/marker.h \
    src/map/models/image.h \
    src/map/global/markermanager.h \
    src/network/modules/abstract/remote.h \
    src/network/udpremote.h \
    src/network/tcpdownloader.h \
    src/network/modules/telemetryremote.h \
    src/network/modules/execdremote.h \
    src/network/modules/feedbackremote.h \
    src/network/modules/execd/argumentlist.h \
    src/network/modules/execd/execdargument.h \
    src/config/config.h \
    src/config/sconfig.h \
    src/config/settingsdialog.h \
    src/config/runtimedata.h \
    src/disk/cachemanager.h \
    src/disk/disktools.h \
    src/disk/savethread.h \
    src/image-processing/imagemanager.h \
    src/func/smath.h \
    src/func/stext.h \
    src/func/schecksum.h \
    src/gui/passworddialog.h \
    src/gui/applicationheader.h \
    src/gui/windows/abstract/windowbackend.h \
    src/gui/windows/dialogwindowbackend.h \
    src/gui/windows/markerwindowbackend.h \
    src/gui/windows/autocapturemarkwindowbackend.h \
    src/gui/windows/settingswindowbackend.h \
    src/gui/windows/focuswindowbackend.h \

FORMS += \
    src/coreui.ui \
    src/network/tcpdebug.ui \
    src/gui/passworddialog.ui \
    src/config/settingsdialog.ui \

RESOURCES += \
    src/qml.qrc \
    src/qss.qrc \
    src/osmconfig.qrc \
    resources/resources.qrc \
    appiconwin32.rc \

DEFINES += QMAKE_COMPILATOR

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
