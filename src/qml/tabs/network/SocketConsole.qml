import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import CCL.Charts 1.0

Pane {
    property string name: "Socket Console";
    property alias color: histogram.histogramColor;

    function logdata(str, sizeof)
    {
        //textarea.append(str);
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

        TextArea { id: textarea;
            anchors.fill: parent;
            anchors.topMargin: 0;
            anchors.bottomMargin: 0;
            anchors.margins: 5;
            placeholderText: "Нет вывода с сокета.";
            placeholderTextColor: Theme.color("dark3");
            font.family: root.monofont;
            color: Theme.color("light0");
            font.bold: true;
            font.pixelSize: 12;
            selectByMouse: true;
            readOnly: true;
            selectedTextColor: "#2E3440";
            selectionColor: "#B48EAD";
            textFormat: Text.RichText;
            wrapMode: Text.WordWrap;
            background: null;

            function append(strAdd) {
                text = strAdd + text;
                if(lineCount >= 20)
                    text = "";
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

        CCLRealtimeHistogram { id: histogram;
            anchors.fill: parent;
            histogramColor: Theme.color("orange");
            horizontalAxisMaxValue: 30000;
            verticalAxisMaxValue: 512;
            interval: 1000;
        }
    }
}
