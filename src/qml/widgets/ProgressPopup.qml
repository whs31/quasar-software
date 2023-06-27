import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Theme 1.0

Pane { id: control;
    property real progress: 0;
    property bool shown: progress !== 0 && progress !== 100;
    property string text: "Загрузка...";

    opacity: shown ? 0.9 : 0;
    Behavior on opacity { NumberAnimation { duration: 300; } }
    enabled: shown;

    ColumnLayout {
        spacing: 10;

        Text {
            text: control.text;
            font.family: root.mainfont;
            font.bold: true;
            color: ColorTheme.active.color(ColorTheme.Text)
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
                Material.accent: value === 0 ? ColorTheme.active.color(ColorTheme.Text) : value > 75 ? ColorTheme.active.color(ColorTheme.Green)
                                                                                  : value > 40 ? ColorTheme.active.color(ColorTheme.Yellow)
                                                                                  : ColorTheme.active.color(ColorTheme.Red);
                Layout.fillWidth: true;
                Layout.fillHeight: true;
            }

            Text {
                text: Number(progress).toFixed(0) + "%";
                font.family: root.mainfont;
                font.bold: true;
                color: progress === 0 ? ColorTheme.active.color(ColorTheme.Text) : progress > 75 ? ColorTheme.active.color(ColorTheme.Green)
                                                                              : progress > 40 ? ColorTheme.active.color(ColorTheme.Yellow)
                                                                              : ColorTheme.active.color(ColorTheme.Red);
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
