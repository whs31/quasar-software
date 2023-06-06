import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15 // LEGACY

import Theme 1.0
import Network 1.0

Pane {
    property string name: "Ping Console";

    Material.elevation: 6;
    Material.background: Theme.color("dark1");

    Rectangle { id: header;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: -12;
        color: Theme.color("dark2");
        height: 24;

        Text {
            anchors.fill: parent;
            anchors.leftMargin: 3;
            font {
                family: root.mainfont
                bold: true
                pixelSize: 15
            }
            text: name;
            color: Theme.color("light1");
        }
    }

    Rectangle { id: textareabackground;
        color: Theme.color("dark1");
        anchors {
            top: header.bottom
            topMargin: 12
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Column {
            Row {
                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 15
                    }
                    text: Network.de10Status === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                   : "НЕТ СОЕДИНЕНИЯ";
                    color: Theme.color("light1");
                }
            }

            Row {
                Text {
                    font {
                        family: root.mainfont
                        bold: true
                        pixelSize: 15
                    }
                    text: Network.jetsonStatus === 0 ? "СОЕДИНЕНИЕ ДОСТУПНО"
                                                     : "НЕТ СОЕДИНЕНИЯ";
                    color: Theme.color("light1");
                }
            }
        }
    }
}
