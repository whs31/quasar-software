import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import QuaSAR.API 1.0

import Theme 1.0
import "../../../widgets" as Widgets

Pane {
    Material.elevation: 200

    RowLayout {
        spacing: -2

        RoundButton {
            property var m_icons: ["qrc:/icons/vector/toolbar/angle.svg", "qrc:/icons/vector/images/shot.svg", "qrc:/icons/vector/network/stream.svg"]
            property var m_labels: ["Телескопический", "Полосовой", "Потоковый"]
            property var m_colors: [ColorTheme.active.color(ColorTheme.Accent), ColorTheme.active.color(ColorTheme.Yellow), ColorTheme.active.color(ColorTheme.Maroon)]

            id: button_ToggleMode

            enabled: !button_FormImage.checked
            Layout.preferredHeight: 45
            height: 40
            radius: 4
            icon.source: m_icons[NetworkAPI.currentFormingMode]
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            text: m_labels[NetworkAPI.currentFormingMode]
            Material.elevation: 30
            Material.background: m_colors[NetworkAPI.currentFormingMode]
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)

            onPressed: {
                if(NetworkAPI.currentFormingMode < 2)
                    NetworkAPI.currentFormingMode += 1
                else
                    NetworkAPI.currentFormingMode = 0
            }

            Widgets.TT { txt: "Переключение между режимами работы РЛС" }
        }

        RoundButton {
            property string checkstate_string: checked ? "Остановка" : "Начало"
            id: button_FormImage

            Layout.preferredHeight: 45
            font.family: root.mainfont
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/images/focus.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            text: NetworkAPI.currentFormingMode === Net.Telescopic ? "Формирование изображения"
                  : NetworkAPI.currentFormingMode === Net.Strip ? checkstate_string + " записи"
                  : checkstate_string + " потока"
            checkable: NetworkAPI.currentFormingMode !== Net.Telescopic
            Material.elevation: 30
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: checked ? ColorTheme.active.color(ColorTheme.Red)
                                         : button_ToggleMode.m_colors[NetworkAPI.currentFormingMode]
            onPressed: {
                if(NetworkAPI.currentFormingMode === Net.Telescopic)
                    NetworkAPI.execute(Net.FormTelescopic)
            }
            onCheckedChanged: {
                if(checked) {
                    if(NetworkAPI.currentFormingMode === Net.Strip) {
                        NetworkAPI.execute(Net.StripStart);
                        NetworkAPI.remote.isRecordingStrip = true;
                    }
                    else {
                        NetworkAPI.execute(Net.StreamStart);
                        NetworkAPI.remote.isRecordingStrip = true;
                    }
                }
                else {
                    if(NetworkAPI.currentFormingMode === Net.Strip) {
                        NetworkAPI.execute(Net.StripStop);
                        NetworkAPI.remote.isRecordingStrip = false;
                    }
                    else {
                        NetworkAPI.execute(Net.StreamStop);
                        NetworkAPI.remote.isRecordingStrip = false;
                    }
                }
            }

            Behavior on implicitWidth {
                NumberAnimation {
                    easing.type: Easing.Linear
                    duration: 100
                }
            }
        }

        ComboBox {
            property var descriptions: ["Разрешение до 0.5 м, дальность до 8 км", "Разрешение до 1 м, дальность до 15 км, скорость до 500 км/ч",
                "Разрешение до 1.5 м, дальность до 17 км, скорость до 500 км/ч", "Разрешение до 0.3 м, дальность до 9 км, скорость до 200 км/ч",
                "Разрешение до 0.8 м, дальность до 15 км, скорость до 185 км/ч", "Разрешение до 0.5 м, дальность до 30 км, скорость до 120 км/ч",
                "Разрешение до 0.3 м, дальность до 17 км, скорость до 120 км/ч"]

            Layout.preferredHeight: 45
            currentIndex: 0
            model: ["М1", "М2", "М3", "М4", "М6", "М7"]
            onCurrentValueChanged: {
                let val = (currentIndex + 1);
                if (val === 6)
                    val = 7;

                if (val === 5)
                    val = 6;

                NetworkAPI.setArgument("-m", val, Net.Form);
            }

            font {
                family: root.mainfont
                pixelSize: 14
                weight: Font.Bold
            }

            Widgets.TT { txt: parent.descriptions[parent.currentIndex] }
        }

        RoundButton {
            id: button_Calibrate

            Layout.preferredHeight: 45
            font.family: root.mainfont
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/images/terrain.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            Material.elevation: 30
            Material.foreground: ColorTheme.active.color(ColorTheme.Dark)
            Material.background: ColorTheme.active.color(ColorTheme.PrimaryDark)
            onPressed: dialogwindow.open("Калибровка высоты", "Выполнить калибровку высоты? Убедитесь, что БПЛА находится на земле.", "info", 17)

            Connections {
                function onClosed(status, uid) {
                    if (uid === 17 && status === true) {
                        console.log("[GUI] Calibrating altitude");
                        NetworkAPI.telemetry.seaLevel = NetworkAPI.telemetry.position.altitude;
                    }
                }

                target: dialogwindow
            }

            Widgets.TT { txt: "Выполнить калибровку высоты над рельефом в точке старта" }
        }

        RoundButton {
            id: button_FormParameters

            checkable: true
            checked: false
            Layout.preferredHeight: 45
            height: 40
            radius: 4
            icon.source: "qrc:/icons/vector/common/tune.svg"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            Material.elevation: 30
            Material.foreground: ColorTheme.active.color(ColorTheme.Text)
            Material.background: ColorTheme.active.color(ColorTheme.Surface)
            onCheckedChanged: panel_FormParameters.shown = checked

            Widgets.TT { txt: "Параметры формирования радиолокационных изображений" }
        }
    }

    Behavior on implicitWidth { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200 } }
}
