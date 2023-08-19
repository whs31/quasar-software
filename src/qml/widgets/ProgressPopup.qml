import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

Pane { id: control;
    property real progress: 0;
    property bool shown: progress !== 0 && progress !== 100;
    property string text: "Загрузка...";

    opacity: shown ? 0.9 : 0;
    Behavior on opacity { NumberAnimation { duration: 300; } }
    enabled: shown;

    layer.enabled: true
    layer.effect: DropShadow {
        samples: 16
        radius: 16
        horizontalOffset: 6
        verticalOffset: 6
        opacity: 0.5
    }

    ColumnLayout {
        spacing: 10;

        Text {
            text: control.text;
            font.family: root.mainfont;
            font.bold: true;
            color: theme.text
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
                Material.accent: value === 0 ? theme.text : value > 75 ? theme.green
                                                          : value > 40 ? theme.yellow
                                                          : theme.red
                Layout.fillWidth: true;
                Layout.fillHeight: true;
            }

            Text {
                text: Number(progress).toFixed(0) + "%";
                font.family: root.mainfont;
                font.bold: true;
                color: progress === 0 ? theme.text : progress > 75 ? theme.green
                                                   : progress > 40 ? theme.yellow
                                                   : theme.red
                font.pixelSize: 14;
                Layout.fillHeight: true;
                Layout.preferredWidth: 50;
                Layout.alignment: Qt.AlignRight
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
            }
        }
    }
}
