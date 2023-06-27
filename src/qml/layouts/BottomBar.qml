import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0
import Config 1.0

import "bottombar" as Bottom
import "../widgets" as Widgets

Rectangle {
    color: ColorTheme.active.color(ColorTheme.BaseShade)

    Bottom.StatusWidget { id: c_StatusWidget;
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        anchors.top: parent.top;
    }

    Flickable {
        anchors.left: c_StatusWidget.right;
        anchors.leftMargin: 16;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: layout_SharedToolbar.left;
        clip: true;
        interactive: true;
        contentWidth: c_InfoPanel.width;
        flickableDirection: Flickable.HorizontalFlick;

        Bottom.InfoPanel { id: c_InfoPanel; }
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
            icon.source: Network.connected ? "qrc:/icons/vector/network/wifi_off.svg"
                                           : "qrc:/icons/vector/network/wifi.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            text: Network.connected ? "Отключиться" : "Подключиться к РЛС";
            Material.elevation: 30;
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: Network.connected ? ColorTheme.active.color(ColorTheme.Red)
                                                   : ColorTheme.active.color(ColorTheme.PrimaryLightest)
            Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }
            Behavior on opacity { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }

            onPressed: {
                if(Network.connected)
                    Network.stop();
                else
                {
                    Network.begin(Network.stringifyIP(Config.remoteIP, Config.telemetryPort),
                                  Network.stringifyIP(Config.localIP, Config.telemetryRecvPort),
                                  Config.telemetryFrequency,
                                  Network.stringifyIP(Config.remoteIP, Config.execdPort),
                                  Network.stringifyIP(Config.localIP, Config.feedbackPort),
                                  Network.stringifyIP(Config.localIP, Config.tcpLFSPort),
                                  Network.stringifyIP(Config.localIP, Config.udpLFSPort)
                    );
                    Network.executeCommand(Net.RemoteStorageStatus);
                    timeout = true;
                    disconnect_timer.start();
                }
            }

            Timer { id: disconnect_timer; running: false; repeat: false; interval: 3000; onTriggered: {
                    if(!Network.connected)
                        Network.stop();
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
            onPressed: {
                if(c_SettingsWindow.visible === true)
                    c_SettingsWindow.hide();
                else
                    c_SettingsWindow.show();
            }

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
