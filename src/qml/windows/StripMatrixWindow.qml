import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import LPVL.Charts 1.0
import ImageProcessing 1.0
import Theme 1.0

Window {
    Material.theme: Material.Dark;
    Material.accent: Theme.color("color1");
    Material.primary: Theme.color("accent");
    Material.foreground: Theme.color("light0");
    Material.background: Theme.color("dark1");

    width: 900;
    height: 500;

    color: Theme.color("dark0");
    modality: Qt.NonModal;
    title: "Матрица полосового изображения";

    onVisibleChanged: {
        if(!visible)
        {
            console.log("[OPENGL] Cleanup of matrix plot.");
            plot.clean();
        }
    }

    LPVLMatrixPlot { id: plot;
        anchors.fill: parent;
        anchors.margins: 50;
        anchors.bottomMargin: 100;
    }

    Connections {
        target: ImageProcessing;
        function onStripVector8bit(vec, r, c)
        {
            plot.set(vec, r, c);
            show();
        }
    }

    Pane {
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        Row {
            spacing: 20;

            CheckBox {
                text: "Оттенки серого";
                font.family: root.mainfont;
                font.bold: true;
                checked: false;
                onCheckedChanged: plot.grayscale = checked;
            }

            RowLayout {
                Text {
                    Layout.alignment: Qt.AlignVCenter;
                    Layout.fillHeight: true;
                    text: "Контрастность матрицы: ";
                    font.family: root.mainfont;
                    verticalAlignment: Text.AlignVCenter;
                    color: Theme.color("light0");
                    font.bold: true;
                }

                Slider {
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    from: 0;
                    to: 1;
                    value: 1;
                    onValueChanged: plot.brightness = value;
                }
            }
        }
    }
}
