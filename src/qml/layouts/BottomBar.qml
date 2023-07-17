import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Config 1.0

import QuaSAR.API 1.0

import "bottombar" as Bottom
import "../widgets" as Widgets

Rectangle {
    color: ColorTheme.active.color(ColorTheme.BaseShade)

    Bottom.ConnectionStatusIndicator {
        id: connection_status_indicator
        anchors {
            left: parent.left
            leftMargin: 6
            verticalCenter: parent.verticalCenter
        }
        height: 35
        width: 300
        connected: NetworkAPI.isConnected
    }

    Flickable {
        id: scroll_area
        anchors {
            left: connection_status_indicator.right
            leftMargin: 14
            top: parent.top
            topMargin: 3
            bottom: parent.bottom
            right: layout_SharedToolbar.left
        }

        clip: true
        interactive: true
        contentWidth: 1100
        flickableDirection: Flickable.HorizontalFlick

        Bottom.TelemetryWidget {
            id: telemetry_widget
            height: scroll_area.height - 4
        }
    }

    Row { id: layout_SharedToolbar;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        BusyIndicator {
            enabled: !button_Connect.enabled;
            opacity: enabled ? 1 : 0;
            height: 40;
            width: 40;
            running: enabled;
            Behavior on opacity { NumberAnimation { easing.type: Easing.Linear; duration: 300; } }
        }

        RoundButton { id: button_Connect;
            property bool timeout: false;

            enabled: !timeout;
            opacity: enabled ? 1 : 0.5;
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: NetworkAPI.isConnected ? "qrc:/icons/vector/network/wifi_off.svg"
                                                : "qrc:/icons/vector/network/wifi.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            text: NetworkAPI.isConnected ? "Отключиться" : "Подключиться к РЛС";
            Material.elevation: 30;
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: NetworkAPI.isConnected ? ColorTheme.active.color(ColorTheme.Red)
                                                        : ColorTheme.active.color(ColorTheme.PrimaryLightest)
            Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }
            Behavior on opacity { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

            onPressed: {
                if(NetworkAPI.isConnected)
                    NetworkAPI.stop();
                else
                {
                    NetworkAPI.start(NetworkAPI.stringify(Settings.io.parameter("ip/de10"), Settings.io.parameter("port/telemetry-request")),
                                     NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/telemetry-receive")),
                                     Settings.io.parameter("misc/telemetry-frequency"),
                                     NetworkAPI.stringify(Settings.io.parameter("ip/de10"), Settings.io.parameter("port/execd")),
                                     NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/stdout")),
                                     NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/tcp")),
                                     NetworkAPI.stringify(Settings.io.parameter("ip/computer"), Settings.io.parameter("port/strip"))
                    );
                    NetworkAPI.execute(Net.RemoteStorageStatus);
                    timeout = true;
                    disconnect_timer.start();
                }
            }

            Timer { id: disconnect_timer; running: false; repeat: false; interval: 3000; onTriggered: {
                    if(!NetworkAPI.isConnected)
                        NetworkAPI.stop();
                    button_Connect.timeout = false;
                }
            }
        }

        RoundButton { id: button_Settings;
            font.family: root.mainfont;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/common/settings.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            onPressed: settingswindow.shown = !settingswindow.shown

            Widgets.TT { ff: root.mainfont; txt: "Настройки программы"; }
        }

        RoundButton { id: button_About;
            font.family: root.mainfont;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/common/info.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            onPressed: {
                if(c_InfoWindow.b_Shown)
                    c_InfoWindow.b_Shown = false;
                else
                    c_InfoWindow.b_Shown = true;
            }

            Widgets.TT { ff: root.mainfont; txt: "О программе"; }
        }

        RoundButton { id: button_ToggleDebug;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/common/terminal.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            onPressed: root.consoleshown = !root.consoleshown;

            Widgets.TT { ff: root.mainfont; txt: "Консоль разработчика"; }
        }

        RoundButton { id: button_ToggleVT100;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/vector/common/remote_display.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30;
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            onPressed: root.vt100termshown = !root.vt100termshown;

            Widgets.TT { ff: root.mainfont; txt: "Консоль РЛС"; }
        }
    }
}
