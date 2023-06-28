import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15 // LEGACY

import Charts 1.0
import Theme 1.0

Pane {
    property string name: "Socket Console";
    property alias color: plot.plottingColor;

    function logdata(str, sizeof, out)
    {
        listview.append(str, sizeof, out);
        plot.append(sizeof);
    }

    Material.elevation: 6;
    Material.background: ColorTheme.active.color(ColorTheme.BaseShade)

    Rectangle { id: header;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: -12;
        color: ColorTheme.active.color(ColorTheme.Surface)
        height: 24;

        Text {
            anchors.fill: parent;
            anchors.leftMargin: 3;
            text: name;
            font.family: root.mainfont;
            color: ColorTheme.active.color(ColorTheme.Text)
            font.bold: true;
            font.pixelSize: 15;
        }
    }

    Rectangle { id: textareabackground;
        color: ColorTheme.active.color(ColorTheme.Dark)
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
            interactive: true;
            clip: true;
            delegate: Row {
                spacing: 5;
                Rectangle {
                    height: 12;
                    width: 30;
                    radius: 6;
                    color: direction ? ColorTheme.active.color(ColorTheme.Orange) : ColorTheme.active.color(ColorTheme.Green)

                    Text {
                        font.family: root.monofont;
                        anchors.centerIn: parent;
                        color: ColorTheme.active.color(ColorTheme.Dark)
                        font.bold: true;
                        font.pixelSize: 12;
                        text: direction ? "OUT" : "IN";
                    }
                }

                Text {
                    text: txt;
                    font.family: root.monofont;
                    color: ColorTheme.active.color(ColorTheme.Text)
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
        color: ColorTheme.active.color(ColorTheme.BaseShade)

        RealtimeLinePlot {
            id: plot
            anchors.fill: parent
            from: 0
            to: 256
            backgroundColor: ColorTheme.active.color(ColorTheme.Surface)
            plottingColor: ColorTheme.active.color(ColorTheme.Primary)
            foregroundColor: ColorTheme.active.color(ColorTheme.Text)
            interval: 1
            seconds: 30
            drawAxes: false
            layer {
                enabled: true
                smooth: true
                samples: 8
                effect: OpacityMask {
                    maskSource: parent
                }
            }
        }
    }
}
