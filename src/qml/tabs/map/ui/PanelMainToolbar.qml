import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Network 1.0
import Config 1.0

import "../../../widgets" as Widgets

Pane {
    property int mode; // 0 = telescopic, 1 = strip

    Material.elevation: 200;
    Behavior on implicitWidth { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }

    RowLayout {
        spacing: -2;

        RoundButton { id: button_ToggleMode;
            enabled: !button_FormImage.checked;
            Layout.preferredHeight: 45;
            height: 40;
            radius: 4;
            icon.source: mode === 0 ? "qrc:/icons/google-material/camera.png"
                                    : "qrc:/icons/google-material/videocamera.png";
            icon.color: Theme.color("dark0");
            checkable: true;
            Material.elevation: 30;
            Material.background: mode === 0 ? Theme.color("accent")
                                            : Theme.color("yellow");
            onCheckedChanged: checked ? mode = 1 : mode = 0;

            Widgets.TT { ff: root.mainfont; txt: "Переключение между телескопическим и полосовым режимом"; }
        }

        RoundButton { id: button_FormImage;
            Layout.preferredHeight: 45;
            Behavior on implicitWidth { NumberAnimation { easing.type: Easing.Linear; duration: 100; } }
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/take-photo.png";
            icon.color: Theme.color("dark0");
            text: mode === 0 ? "Формирование изображения"
                         : checked
                             ? "Остановка записи"
                             : "Начало записи";
            checkable: mode === 1;
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: mode === 0 ? Theme.color("accent")
                                            : checked
                                            ? Theme.color("orange")
                                            : Theme.color("yellow");
            onPressed: {
                if(!checkable)
                    Network.executeCommand(Net.FormImage);
            }

            onCheckedChanged: {
                if(checked)
                    Network.executeCommand(Net.StartStrip);
                else
                    Network.executeCommand(Net.StopStrip);
            }
        }

        ComboBox {
            Layout.preferredHeight: 45;
            font {
                family: root.mainfont;
                pixelSize: 14;
                weight: Font.Bold;
            }

            currentIndex: 0;
            model: [ "М1", "М2", "М3", "М4",
                "М6", "М7", ];
            onCurrentValueChanged: {
                let val = (currentIndex + 1);
                if(val === 6)
                    val = 7;
                if(val === 5)
                    val = 6;
                Network.setArgument("-m", val, Net.Form);
            }
        }

        RoundButton { id: button_Calibrate;
            Layout.preferredHeight: 45;
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/water.png"
            icon.color: Theme.color("dark0");
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Theme.color("color0");
            onPressed: dialogwindow.open("Калибровка высоты", "Выполнить калибровку высоты? Убедитесь, что БПЛА находится на земле.", "info", 17);

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 17 && status === true) {
                        console.log("[GUI] Calibrating altitude");
                        Network.telemetry.seaLevel = Network.telemetry.altitude;
                    }
                }
            }

            Widgets.TT { ff: root.mainfont; txt: "Выполнить калибровку высоты над рельефом в точке старта"; }
        }

        RoundButton { id: button_ClearDisk;
            Layout.preferredHeight: 45;
            font.family: root.mainfont;
            height: 40;
            radius: 4;
            icon.source: "qrc:/icons/google-material/delete.png"
            icon.color: Theme.color("dark0");
            Material.elevation: 30;
            Material.foreground: Theme.color("dark0");
            Material.background: Theme.color("red");
            onPressed: dialogwindow.open("Очистка удаленного диска", "Вы уверены, что хотите очистить удаленное хранилище на РЛС?", "error", 27);

            Connections {
                target: dialogwindow;
                function onClosed(status, uid) {
                    if(uid === 27 && status === true) {
                        console.log("[GUI] Clearing remote storage");
                        Network.executeCommand(Net.ClearRemoteStorage);
                    }
                }
            }

            Widgets.TT { ff: root.mainfont; txt: "Очистить хранилище на РЛС"; }
        }
    }
}

