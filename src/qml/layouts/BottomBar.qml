import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0
import Config 1.0

import "bottombar" as Bottom
import "../widgets" as Widgets

Rectangle {
    color: Theme.color("dark1");

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

        RoundButton { id: button_Connect;
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: Network.connected ? "qrc:/icons/google-material/unlink.png"
                                           : "qrc:/icons/google-material/link.png";
            icon.color: Theme.color("dark0");
            text: Network.connected ? "Отключиться" : "Подключиться к РЛС";
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Network.connected ? Theme.color("red") : Theme.color("color3");
            Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }
            onPressed: {
                if(Network.connected)
                {
                    Network.stopExecdSocket();
                    Network.stopTelemetrySocket();
                    Network.stopTCPSocket();
                    Network.networkDelay = 100;
                }
                else
                {
                    Network.startExecdSocket(Config.remoteIP + ":" + Config.execdPort,
                                             Config.localIP + ":" + Config.feedbackPort);
                    Network.startTelemetrySocket(Config.remoteIP + ":" + Config.telemetryPort,
                                                 Config.remoteIP + ":" + Config.telemetryRecvPort,
                                                 Config.telemetryFrequency);
                    Network.startTCPSocket(Config.localIP + ":" + Config.tcpLFSPort);
                    Network.executeCommand(Net.RemoteStorageStatus);
                    disconnect_timer.start();
                }
            }

            Timer { id: disconnect_timer; running: false; repeat: false; interval: 10000; onTriggered: {
                    if(!Network.connected)
                    {
                        Network.stopExecdSocket();
                        Network.stopTelemetrySocket();
                        Network.stopTCPSocket();
                        Network.networkDelay = 100;
                    }
                }
            }
        }

        RoundButton { id: button_Settings;
            font.family: root.mainfont;
            height: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/settings.png";
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
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
            icon.source: "qrc:/icons/google-material/info.png";
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
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
            icon.source: "qrc:/icons/google-material/terminal.png";
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            onPressed: root.consoleshown = !root.consoleshown;

            Widgets.TT { ff: root.mainfont; txt: "Консоль разработчика"; }
        }

        RoundButton { id: button_ToggleVT100;
            height: 44;
            width: 44;
            radius: 4;
            icon.source: "qrc:/icons/google-material/remote_monitor.png";
            icon.color: Theme.color("light0");
            Material.elevation: 30;
            Material.background: Theme.color("dark1");
            onPressed: root.vt100termshown = !root.vt100termshown;

            Widgets.TT { ff: root.mainfont; txt: "Консоль РЛС"; }
        }
    }
}
