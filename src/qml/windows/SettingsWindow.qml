import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Theme 1.0
import Config 1.0

Window {
    Material.theme: Material.Dark
    Material.accent: ColorTheme.active.color(ColorTheme.Yellow)
    Material.primary: ColorTheme.active.color(ColorTheme.Accent)
    Material.foreground: ColorTheme.active.color(ColorTheme.Text)
    Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
    width: 700
    height: 800
    color: ColorTheme.active.color(ColorTheme.Text)
    modality: Qt.NonModal
    title: "Параметры"

    ScrollView {
        id: view

        property bool b_GlobalValid: validator_1.b_Valid && validator_2.b_Valid && validator_3.b_Valid && validator_4.b_Valid && validator_5.b_Valid && validator_6.b_Valid && validator_7.b_Valid && validator_a1.b_Valid && validator_a2.b_Valid && validator_a3.b_Valid && validator_a4.b_Valid

        width: parent.width
        height: parent.height
        contentWidth: column.width
        contentHeight: column.height
        clip: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: buttonGroup.top
        anchors.bottomMargin: 5

        Column {
            id: column

            width: parent.width
            spacing: 30

            Pane {
                id: panel_Network

                x: 25
                height: 890
                Material.elevation: 50
                width: view.width - 50

                Rectangle {
                    id: header1

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: -12
                    color: ColorTheme.active.color(ColorTheme.Surface)
                    height: 24

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 3
                        text: "СЕТЕВЫЕ ПОДКЛЮЧЕНИЯ"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.bold: true
                        font.pixelSize: 15
                    }

                }

                GridLayout {
                    columns: 2
                    anchors.top: header1.bottom
                    anchors.margins: 5
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Text {
                        text: "IP-адрес РЛМ:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_1

                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.remoteIP
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.remoteIP = text
                    }

                    Text {
                        text: "IP-адрес вычислителя:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_a1

                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.jetsonIP
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.jetsonIP = text
                    }

                    Text {
                        text: "IP-адрес навигации:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_a2

                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.navIP
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.navIP = text
                    }

                    Text {
                        text: "IP-адрес коммутатора антенн:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_a3

                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.utl1IP
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.utl1IP = text
                    }

                    Text {
                        text: "IP-адрес коммутатора питания:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_a4

                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.utl2IP
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.utl2IP = text
                    }

                    Text {
                        text: "IP-адрес АРМ:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_2

                        property bool b_Valid: text.split(".").length === 4 && /^[0-9.]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.localIP
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.localIP = text
                    }

                    Text {
                        text: "Порт сокета телеметрии:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_3

                        property bool b_Valid: /^[0-9]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.telemetryPort
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.telemetryPort = text
                    }

                    Text {
                        text: "Порт входящей телеметрии:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_x

                        property bool b_Valid: /^[0-9]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.telemetryRecvPort
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.telemetryRecvPort = text
                    }

                    Text {
                        text: "Порт сокета выполнения команд:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_4

                        property bool b_Valid: /^[0-9]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.execdPort
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.execdPort = text
                    }

                    Text {
                        text: "Порт сокета обратной связи:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_5

                        property bool b_Valid: /^[0-9]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.feedbackPort
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.feedbackPort = text
                    }

                    Text {
                        text: "Порт TCP-загрузчика:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_6

                        property bool b_Valid: /^[0-9]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.tcpLFSPort
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.tcpLFSPort = text
                    }

                    Text {
                        text: "Порт UDP-загрузчика:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        id: validator_7

                        property bool b_Valid: /^[0-9]*$/.test(text)

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.udpLFSPort
                        Layout.alignment: Qt.AlignRight
                        color: b_Valid ? ColorTheme.active.color(ColorTheme.Text) : ColorTheme.active.color(ColorTheme.Red)
                        onEditingFinished: Config.udpLFSPort = text
                    }

                    Text {
                        text: "Частота запроса телеметрии, c:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        text: Number(Config.telemetryFrequency).toFixed(2)
                        Layout.alignment: Qt.AlignRight
                        onEditingFinished: Config.telemetryFrequency = parseFloat(text)

                        font {
                            family: root.mainfont
                            pixelSize: 14
                            bold: true
                        }

                        validator: DoubleValidator {
                            decimals: 2
                            bottom: 0
                            top: 1000
                            locale: "en_US"
                        }

                    }

                    CheckBox {
                        checked: Config.proxyEnabled
                        text: "Использовать прокси"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.proxyEnabled = checked
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    Text {
                        text: "Маркер TCP-сокета:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    ComboBox {
                        id: control_TCPMarker

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        width: 250
                        currentIndex: Config.tcpMarker === "\n" ? 1 : 0
                        model: ["NULL", "NEWLINE"]
                        Layout.alignment: Qt.AlignRight
                        onCurrentValueChanged: {
                            if (currentValue === "NULL")
                                Config.tcpMarker = "\0";
                            else
                                Config.tcpMarker = "\n";
                        }
                    }

                    CheckBox {
                        checked: Config.redirect
                        text: "Перенаправлять вывод РЛС"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.redirect = checked
                    }

                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    Text {
                        enabled: Config.redirect
                        text: "Адрес для перенаправления вывода:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    TextField {
                        enabled: Config.redirect
                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        text: Config.redirectAddress
                        Layout.alignment: Qt.AlignRight
                        color: ColorTheme.active.color(ColorTheme.Text)
                        onEditingFinished: Config.redirectAddress = text
                    }
                }

            }

            Pane {
                id: panel_UAV

                x: 25
                Material.elevation: 50
                width: view.width - 50
                height: 80

                Rectangle {
                    id: header3

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: -12
                    color: ColorTheme.active.color(ColorTheme.Surface)
                    height: 24

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 3
                        text: "ПАРАМЕТРЫ НОСИТЕЛЯ"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.bold: true
                        font.pixelSize: 15
                    }

                }

                GridLayout {
                    columns: 2
                    anchors.top: header3.bottom
                    anchors.margins: 5
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Text {
                        text: "Положение антенны:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    ComboBox {
                        id: control_AntennaPosition

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        width: 250
                        currentIndex: Config.antennaAlignment ? 1 : 0
                        model: ["Слева", "Справа"]
                        Layout.alignment: Qt.AlignRight
                        onCurrentValueChanged: {
                            if (currentValue === "Слева")
                                Config.antennaAlignment = 0;
                            else
                                Config.antennaAlignment = 1;
                        }
                    }

                }

            }

            Pane {
                id: panel_Geopositioning

                x: 25
                height: 230
                Material.elevation: 50
                width: view.width - 50

                Rectangle {
                    id: header4

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: -12
                    color: ColorTheme.active.color(ColorTheme.Surface)
                    height: 24

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 3
                        text: "ПАРАМЕТРЫ ГЕОПРИВЯЗКИ"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.bold: true
                        font.pixelSize: 15
                    }

                }

                GridLayout {
                    columns: 2
                    anchors.top: header4.bottom
                    anchors.margins: 5
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Text {
                        text: "Общая коррекция угла:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    SpinBox {
                        Layout.alignment: Qt.AlignRight
                        font.family: root.mainfont
                        font.pixelSize: 14
                        font.bold: true
                        from: -180
                        to: 180
                        value: Config.angleCorrection
                        onValueChanged: Config.angleCorrection = value
                        textFromValue: function(value, locale) {
                            return Number(value).toLocaleString(locale, 'f', 0) + "°";
                        }
                    }

                    Text {
                        text: "Коррекция тета-азимута:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    SpinBox {
                        Layout.alignment: Qt.AlignRight
                        font.family: root.mainfont
                        font.bold: true
                        font.pixelSize: 14
                        from: 0
                        to: 30
                        value: Config.thetaAzimuthCorrection
                        onValueChanged: Config.thetaAzimuthCorrection = value
                        textFromValue: function(value, locale) {
                            return Number(value).toLocaleString(locale, 'f', 0) + "°";
                        }
                    }

                    CheckBox {
                        checked: Config.useRadians
                        text: "Телеметрия в радианах"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.useRadians = checked
                    }

                    CheckBox {
                        checked: Config.useDriftAngle
                        text: "Учитывать угол сноса"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.useDriftAngle = checked
                    }

                    CheckBox {
                        checked: Config.overrideImageHeight
                        text: "Коррекция РЛИ по путевой дальности"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.overrideImageHeight = checked
                    }

                    CheckBox {
                        checked: Config.cutImage
                        text: "Использовать маску для РЛИ"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.cutImage = checked
                    }

                }

            }

            Pane {
                id: panel_Application

                x: 25
                height: 130
                Material.elevation: 50
                width: view.width - 50

                Rectangle {
                    id: header5

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: -12
                    color: ColorTheme.active.color(ColorTheme.Surface)
                    height: 24

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 3
                        text: "ПРИЛОЖЕНИЕ"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.bold: true
                        font.pixelSize: 15
                    }

                }

                GridLayout {
                    columns: 2
                    anchors.top: header5.bottom
                    anchors.margins: 5
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Text {
                        text: "Тема приложения:"
                        font.family: root.mainfont
                        color: ColorTheme.active.color(ColorTheme.Text)
                        font.pixelSize: 14
                        Layout.alignment: Qt.AlignLeft
                    }

                    ComboBox {
                        id: control_Theme

                        font.family: root.mainfont
                        font.weight: Font.Bold
                        font.pixelSize: 14
                        implicitWidth: 250
                        currentIndex: Config.theme === "dark" ? 1 : 0
                        model: ["Контрастная", "Темная"]
                        Layout.alignment: Qt.AlignRight
                        onCurrentValueChanged: {
                            if (currentValue === "Контрастная")
                                Config.theme = "contrast";
                            else
                                Config.theme = "dark";
                        }
                    }

                    CheckBox {
                        checked: Config.enableDebugStrip
                        text: "Разрешить упрощенные полосовые изображения"
                        font.family: root.mainfont
                        font.pixelSize: 14
                        onCheckedChanged: Config.enableDebugStrip = checked
                    }
                }
            }
        }
    }

    Row {
        id: buttonGroup

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        RoundButton {
            id: button_Save

            width: 200
            enabled: view.b_GlobalValid
            font.family: root.mainfont
            font.weight: Font.Bold
            height: 44
            radius: 4
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            text: "Применить"
            onPressed: {
                Config.save();
                hide();
            }
        }

        RoundButton {
            id: button_Cancel

            width: 200
            font.family: root.mainfont
            font.weight: Font.Bold
            height: 44
            radius: 4
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            text: "Отмена"
            onPressed: {
                Config.revert();
                hide();
            }
        }

    }

}
