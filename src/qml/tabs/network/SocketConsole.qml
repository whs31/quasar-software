import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15 // LEGACY

import LPVL.Charts 1.0
import Theme 1.0

Pane {
    property string name: "Socket Console";
    property color color: "red";
    property alias color: plot.plottingColor;

    function logdata(str, sizeof, out)
    {
        listview.append(str, sizeof, out);
        plot.append(sizeof);
    }

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
            text: name;
            font.family: root.mainfont;
            color: Theme.color("light1");
            font.bold: true;
            font.pixelSize: 15;
        }
    }

    Rectangle { id: textareabackground;
        color: Theme.color("dark0");
        anchors.top: header.bottom;
        anchors.topMargin: 12;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom; // temp;
        anchors.bottomMargin: 100;

        ListModel { id: listmodel; }
        ListView { id: listview;
            model: listmodel;
            anchors.fill: parent;
            anchors.margins: 5;
            clip: true;
            delegate: Row {
                spacing: 5;
                Rectangle {
                    height: 12;
                    width: 30;
                    radius: 6;
                    color: direction ? Theme.color("accent") : Theme.color("dark3");

                    Text {
                        font.family: root.monofont;
                        anchors.centerIn: parent;
                        color: direction ? Theme.color("dark0") : Theme.color("light0");
                        font.bold: true;
                        font.pixelSize: 12;
                        text: direction ? "OUT" : "IN";
                    }
                }

                Text {
                    text: txt;
                    font.family: root.monofont;
                    color: Theme.color("light0");
                    font.bold: true;
                    font.pixelSize: 12;
                    textFormat: Text.RichText;
                }
            }

            function append(strAdd, size, direction) {
                if(listmodel.count > 18)
                    listmodel.remove(0, 1);
                listmodel.append({"txt": strAdd, "sizeof": size, "direction": direction});
            }
        }
    }

    Rectangle {
        anchors.top: textareabackground.bottom;
        anchors.topMargin: 6;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 6;
        radius: 15;
        clip: true;
        color: Theme.color("dark1");

        LPVLRealtimeLinePlot { id: plot;
            anchors.fill: parent;
            from: 0;
            to: 255;
            backgroundColor: Theme.color("dark2");
            plottingColor: Theme.color("color1");
            foregroundColor: Theme.color("light0");
            interval: 1;
            seconds: 30;
            drawAxes: false;
            layer.enabled: true;
            layer.smooth: true;
            layer.samples: 8;
            layer.effect: OpacityMask {
                maskSource: parent;
            }
        }
    }
}
