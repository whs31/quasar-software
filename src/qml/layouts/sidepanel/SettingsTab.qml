import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0

Page {
    Material.primary: ColorTheme.active.color(ColorTheme.Primary)
    Material.accent: ColorTheme.active.color(ColorTheme.Primary)
    header: ToolBar {
        Material.primary: ColorTheme.active.color(ColorTheme.Primary)

        RowLayout {
            anchors.fill: parent

            ToolButton {
                icon {
                    source: "qrc:/icons/vector/common/left_small.svg"
                    color: ColorTheme.active.color(ColorTheme.Dark)
                }
                flat: true
                Layout.fillHeight: true

                onPressed: drawer.selectedIndex = 0
            }

            Label {
                font {
                    weight: Font.ExtraBold
                    pixelSize: 18
                    capitalization: Font.AllUppercase
                }
                color: ColorTheme.active.color(ColorTheme.Dark)
                Layout.fillWidth: true
                Layout.rightMargin: 25
                horizontalAlignment: Text.AlignHCenter
                text: "Настройки программы"
            }
        }
    }

    component ConfigIPv4Input: RowLayout {
        property string description: "None"
        property string key: "null/null"

        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            Layout.leftMargin: 60

            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.DemiBold; pixelSize: 14 }
        }

        TextField {
            Layout.rightMargin: 30

            validator: RegExpValidator { regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: Settings.io.parameter(key)
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: Settings.setParameter(key, text)
            horizontalAlignment: Text.AlignRight
        }
    }

    component ConfigPortInput: RowLayout {
        property string description: "None"
        property string key: "null/null"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            Layout.leftMargin: 60

            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.DemiBold; pixelSize: 14 }
        }

        TextField {
            Layout.rightMargin: 30

            validator: RegExpValidator { regExp:  /^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: Settings.io.parameter(key)
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            horizontalAlignment: Text.AlignRight
            onEditingFinished: Settings.setParameter(key, text)
        }
    }

    component ConfigDecimalInput: RowLayout {
        property string description: "None"
        property string key: "null/null"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.leftMargin: 60
            Layout.fillWidth: true
            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.DemiBold; pixelSize: 14 }
        }

        TextField {
            Layout.rightMargin: 30

            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: Settings.io.parameter(key)
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            horizontalAlignment: Text.AlignRight
            onEditingFinished: Settings.setParameter(key, text)
        }
    }

    component ConfigCheckbox: RowLayout {
        property string description: "None"
        property string key: "null/null"
        property alias isChecked: comp.checked
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.leftMargin: 60
            Layout.fillWidth: true
            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.DemiBold; pixelSize: 14 }
        }

        Switch {
            id: comp
            Layout.rightMargin: 30
            checked: Settings.io.parameter(key)
            onCheckedChanged: Settings.setParameter(key, checked)
        }
    }

    component Spacer: Item { Layout.fillHeight: true; height: 15 }
    component LargeSpacer: Item { Layout.fillHeight: true; height: 35 }

    component SettingsGroupHeader : ColumnLayout {
        property string headerText: "None"

        spacing: 10
        Layout.fillWidth: true

        Rectangle {
            Layout.fillWidth: true
            height: 1.5
            color: ColorTheme.active.color(ColorTheme.Primary)
        }

        Label {
            Layout.fillWidth: true
            Layout.leftMargin: 50
            font {
                weight: Font.Bold
                pixelSize: 13
            }

            text: parent.headerText
            color: ColorTheme.active.color(ColorTheme.Primary)
        }
    }

    ColumnLayout {
        spacing: 5
        anchors.fill: parent

        ScrollView {
            id: scrollview
            Layout.fillHeight: true
            Layout.fillWidth: true
            implicitHeight: 500;
            implicitWidth: parent.width;
            clip: true;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff;

            ColumnLayout {
                width: scrollview.width - 30;

                SettingsGroupHeader { headerText: "Сетевые подключения" }
                ConfigIPv4Input { description: "IP-адрес РЛС"; key: "ip/de10" }
                ConfigIPv4Input { description: "IP-адрес АРМ"; key: "ip/computer" }
                ConfigIPv4Input { description: "IP-адрес вычислителя"; key: "ip/jetson" }
                ConfigIPv4Input { description: "IP-адрес навигации"; key: "ip/navigation" }
                ConfigIPv4Input { description: "IP-адрес коммутатора антенн"; key: "ip/com1" }
                ConfigIPv4Input { description: "IP-адрес коммутатора питания"; key: "ip/com2" }

                Spacer {}
                ConfigPortInput { description: "Порт сервиса телеметрии"; key: "port/telemetry-request" }
                ConfigPortInput { description: "Порт входящей телеметрии"; key: "port/telemetry-receive" }
                ConfigPortInput { description: "Порт сервиса выполнения команд"; key: "port/execd" }
                ConfigPortInput { description: "Порт обратной связи"; key: "port/stdout" }
                ConfigPortInput { description: "Порт статусной информации"; key: "port/status" }
                ConfigPortInput { description: "Порт сервера TCP-IP"; key: "port/tcp" }
                ConfigPortInput { description: "Порт полосовых изображений"; key: "port/strip" }

                LargeSpacer {}
                SettingsGroupHeader { headerText: "Перенаправление вывода" }
                ConfigCheckbox { id: checkbox_Redirect; description: "Включить перенаправление вывода"; key: "misc/redirect" }
                ConfigIPv4Input { enabled: checkbox_Redirect.isChecked; description: "IP-адрес Telnet-сервера"; key: "ip/redirect" }
                ConfigPortInput { enabled: checkbox_Redirect.isChecked; description: "Порт Telnet-сервера"; key: "port/redirect" }

                LargeSpacer {}
                SettingsGroupHeader { headerText: "Обработка изображений" }
                GridLayout {
                    columns: 2
                    Text {
                        Layout.fillWidth: true
                        Layout.leftMargin: 60
                        text: "Единицы изм. угла в метаданных" + ":"
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font { weight: Font.DemiBold; pixelSize: 14 }
                    }

                    RadioButton {
                        Layout.rightMargin: 30
                        font { weight: Font.Bold; pixelSize: 14 }
                        text: "Градусы"
                        checked: !Settings.io.parameter("image/radians")
                        onPressed: Settings.setParameter("image/radians", false)
                    }

                    Item { Layout.fillHeight: true }

                    RadioButton {
                        Layout.rightMargin: 30
                        font { weight: Font.Bold; pixelSize: 14 }
                        text: "Радианы"
                        checked: Settings.io.parameter("image/radians")
                        onPressed: Settings.setParameter("image/radians", true)
                    }
                }
                ConfigCheckbox { description: "Использовать маску"; key: "image/cut" }
                ConfigCheckbox { description: "Учитывать угол сноса"; key: "image/drift-angle" }
                ConfigDecimalInput { description: "Коррекция θ-азимута"; key: "image/div-correction" }

                LargeSpacer {}
                SettingsGroupHeader { headerText: "Прочие настройки" }
                GridLayout {
                    columns: 2
                    Text {
                        Layout.fillWidth: true
                        Layout.leftMargin: 60
                        text: "Положение антенны на БПЛА" + ":"
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font { weight: Font.DemiBold; pixelSize: 14 }
                    }

                    RadioButton {
                        Layout.rightMargin: 30
                        font { weight: Font.Bold; pixelSize: 14 }
                        text: "Слева"
                        checked: Settings.io.parameter("misc/antenna-alignment") === "left"
                        onPressed: Settings.setParameter("misc/antenna-alignment", "left")
                    }

                    Item { Layout.fillHeight: true }

                    RadioButton {
                        Layout.rightMargin: 30
                        font { weight: Font.Bold; pixelSize: 14 }
                        text: "Справа"
                        checked: Settings.io.parameter("misc/antenna-alignment") === "right"
                        onPressed: Settings.setParameter("misc/antenna-alignment", "right")
                    }
                }
                ConfigDecimalInput { description: "Частота запроса телеметрии, с"; key: "misc/telemetry-frequency" }
                ConfigCheckbox { id: checkbox_Compatibility; description: "Режим совместимости"; key: "misc/compatibility" }
            }
        }

        RowLayout {
            id: dialog_buttons
            Layout.fillWidth: true

            RoundButton {
                id: button_Save

                Layout.fillWidth: true
                height: 44
                radius: 4

                font {
                    family: root.mainfont
                    weight: Font.Bold
                }

                Material.elevation: 30
                Material.background: ColorTheme.active.color(ColorTheme.Surface)

                text: "Сохранить"
                onPressed: {
                    Settings.save()
                    drawer.selectedIndex = 0
                }
            }

            RoundButton {
                id: button_Cancel

                Layout.fillWidth: true
                height: 44
                radius: 4

                font {
                    family: root.mainfont
                    weight: Font.Bold
                }

                Material.elevation: 30
                Material.background: ColorTheme.active.color(ColorTheme.Surface)

                text: "Отменить"
                onPressed: {
                    Settings.revert()
                    drawer.selectedIndex = 0
                }
            }
        }
    }
}
