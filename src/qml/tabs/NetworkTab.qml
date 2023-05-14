import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Network 1.0

import "network" as NetworkTab

Pane {
    Material.background: Theme.color("dark0");

    Flickable {
        anchors.fill: parent;
        clip: true;
        interactive: true;
        flickableDirection: Flickable.HorizontalAndVerticalFlick;
        contentHeight: 1000;
        contentWidth: 1896;

        NetworkTab.SocketConsole { id: panel_TelemetryConsole;
            name: "СОКЕТ ТЕЛЕМЕТРИИ";
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.margins: 5;
            width: 720;
            height: 450;
            color: Theme.color("color3");
        }

        NetworkTab.SocketConsole { id: panel_ExecdConsole;
            name: "СОКЕТ КОМАНД";
            anchors.left: panel_TelemetryConsole.right;
            anchors.top: parent.top;
            anchors.margins: 5;
            width: 345;
            height: 450;
            color: Theme.color("accent");
        }

        NetworkTab.SocketConsole { id: panel_FeedbackConsole;
            name: "СОКЕТ ОБРАТНОЙ СВЯЗИ";
            anchors.left: panel_ExecdConsole.right;
            anchors.top: parent.top;
            anchors.margins: 5;
            width: 425;
            height: 450;
            color: Theme.color("yellow");
        }

        NetworkTab.SocketConsole { id: panel_LFSConsole;
            name: "СОКЕТ TCP-IP";
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.margins: 5;
            width: 380;
            height: 450;
            color: Theme.color("green");
        }

        NetworkTab.SocketConsole { id: panel_StripConsole;
            name: "СОКЕТ UDP LFS";
            anchors.left: parent.left;
            anchors.top: panel_TelemetryConsole.bottom;
            anchors.margins: 5;
            width: 380;
            height: 450;
            color: Theme.color("color0");
        }
    }

    Connections {
        target: Network;
        function onTelemetrySocketMetrics(data, size_bytes) { panel_TelemetryConsole.logdata(data, size_bytes); }
        function onFeedbackSocketMetrics(data, size_bytes) { panel_FeedbackConsole.logdata(data, size_bytes); }
    }
}
