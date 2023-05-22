import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import CCL.Charts 1.0

Pane {
    property string name: "Socket Console";
    property alias color: histogram.histogramColor;

    function logdata(str, sizeof, out)
    {
        listview.append(str, sizeof, out);
        histogram.append(sizeof);
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
                        color: Theme.color("light0");
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
        color: Theme.color("dark0");
        clip: true;

        CCLRealtimeHistogram { id: histogram;
            anchors.fill: parent;
            histogramColor: Theme.color("orange");
            horizontalAxisMaxValue: 30000;
            verticalAxisMaxValue: 512;
            interval: 1000;
        }
    }
}
