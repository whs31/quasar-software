import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Theme 1.0

Pane {
    property real progress: 0;
    property bool shown: progress !== 0 && progress !== 100;

    opacity: shown ? 0.9 : 0;
    Behavior on opacity { NumberAnimation { duration: 300; } }
    enabled: shown;

    ColumnLayout {
        spacing: 10;

        Text {
            text: "Загрузка тайлов оффлайн-карты";
            font.family: root.mainfont;
            font.bold: true;
            color: Theme.color("light1");
            font.pixelSize: 15;
            horizontalAlignment: Text.AlignHCenter;
            Layout.fillWidth: true;
        }

        RowLayout {
            Layout.fillWidth: true;
            ProgressBar {
                from: 0;
                to: 100;
                value: progress;
                indeterminate: progress === 0;
                Material.accent: value === 0 ? Theme.color("light0") : value > 75 ? Theme.color("green")
                                                                                  : value > 40 ? Theme.color("yellow")
                                                                                  : Theme.color("red");
                Layout.fillWidth: true;
                Layout.fillHeight: true;
            }

            Text {
                text: Number(progress).toFixed(0) + "%";
                font.family: root.mainfont;
                font.bold: true;
                color: progress === 0 ? Theme.color("light0") : progress > 75 ? Theme.color("green")
                                                                              : progress > 40 ? Theme.color("yellow")
                                                                              : Theme.color("red");
                font.pixelSize: 14;
                Layout.fillHeight: true;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
            }
        }
    }
}
