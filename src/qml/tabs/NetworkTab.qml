import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0
import Config 1.0

import "network" as NetworkTab

Pane { id: networktab_root;
    Material.background: Theme.color("dark0");

    Flickable {
        anchors.fill: parent;
        clip: true;
        interactive: true;
        flickableDirection: Flickable.HorizontalAndVerticalFlick;
        contentHeight: 1000;
        contentWidth: 1896;

        NetworkTab.SocketConsole { id: panel_TelemetryConsole;
            anchors {
                left: parent.left;
                top: parent.top;
                margins: 5
            }
            name: "СОКЕТ ТЕЛЕМЕТРИИ";
            width: 720;
            height: 450;
            color: Theme.color("color3");
        }

        NetworkTab.SocketConsole { id: panel_ExecdConsole;
            anchors {
                left: panel_TelemetryConsole.right;
                top: parent.top;
                margins: 5
            }
            name: "СОКЕТ КОМАНД";
            width: 1155;
            height: 450;
            color: Theme.color("accent");
        }

        NetworkTab.SocketConsole { id: panel_LFSConsole;
            anchors {
                left: parent.left
                top: panel_TelemetryConsole.bottom
                margins: 5
            }
            name: "СОКЕТ TCP-IP";
            width: 300;
            height: 450;
            color: Theme.color("green");
        }

        NetworkTab.SocketConsole { id: panel_StripConsole;
            anchors {
                left: panel_LFSConsole.right
                top: panel_TelemetryConsole.bottom
                margins: 5
            }
            name: "СОКЕТ UDP LFS";
            width: 300;
            height: 450;
            color: Theme.color("color0");
        }

        NetworkTab.PingConsole { id: panel_pingStatus;
            anchors {
                left: panel_StripConsole.right
                top: panel_TelemetryConsole.bottom
                margins: 5
            }

            name: "ДОСТУП К РЛС";
            width: 500;
            height: 180;
        }
    }

    Connections {
        target: Network;
        function onTelemetrySocketMetrics(data, size_bytes, out) { panel_TelemetryConsole.logdata(data, size_bytes, out); }
        function onExecdSocketMetrics(data, size_bytes, out) { panel_ExecdConsole.logdata(data, size_bytes, out); }
        function onLfsSocketMetrics(data, size_bytes, out) { panel_LFSConsole.logdata(data, size_bytes, out); }
    }
}
