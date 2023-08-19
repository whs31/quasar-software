import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import QuaSAR.API 1.0

import "../../../widgets" as Widgets

Pane {
    property bool shown: false

    height: shown ? implicitHeight : 0
    implicitHeight: 360
    visible: height > 0
    enabled: visible
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 150 } }
    clip: true
    opacity: 0.75
    Material.elevation: 30
    Material.accent: theme.yellow
    Material.background: theme.base

    component FormParametersDecimalInputWithInfo: RowLayout {
        property string description: "None"
        property string key: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        property string details: "None"
        opacity: enabled ? 1 : 0.4

        RoundButton {
            Layout.preferredHeight: 37
            Layout.preferredWidth: 37
            font.family: root.mainfont
            radius: 13
            icon.source: "qrc:/icons/vector/common/question.svg"
            icon.color: theme.text
            Material.elevation: 30

            Widgets.TT {  txt: details }
        }

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        TextField {
            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: NetworkAPI.execd.setArgument(key, text, category)
        }
    }

    component FormParametersDecimalInput: RowLayout {
        property string description: "None"
        property string key: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        TextField {
            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: NetworkAPI.execd.setArgument(key, text, category)
        }
    }

    component FormParametersFilePathInput: RowLayout {
        property string description: "None"
        property string key: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        TextField {
            validator: RegExpValidator { regExp: /^(.+)\/([^\/]+)$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: NetworkAPI.execd.setArgument(key, text, category)
        }
    }

    component FormParametersDualDecimalInput: RowLayout {
        property string description: "None"
        property string firstKey: "--error"
        property string secondKey: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        property string details: "None"
        opacity: enabled ? 1 : 0.4

        RoundButton {
            Layout.preferredHeight: 37
            Layout.preferredWidth: 37
            font.family: root.mainfont
            radius: 13
            icon.source: "qrc:/icons/vector/common/question.svg"
            icon.color: theme.text
            Material.elevation: 30

            Widgets.TT {  txt: details }
        }

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        TextField {
            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: {
                NetworkAPI.execd.setArgument(firstKey, text, category)
                NetworkAPI.execd.setArgument(secondKey, text, category)
            }
        }
    }

    component FormParametersSwitchableDecimalInput: RowLayout {
        property bool switched: true
        property string description: "None"
        property string key: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        Text {
            text: __switch.checked ? "АВТО" : "ВРУЧНУЮ"
            color: __switch.checked ? theme.yellow : theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        Switch {
            id: __switch
            checked: true
        }

        TextField {
            property bool autoMode: __switch.checked
            enabled: !autoMode
            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: NetworkAPI.execd.setArgument(key, text, category)
            onAutoModeChanged: {
                text = defaultValue
                NetworkAPI.execd.setArgument(key, text, category)
            }
        }
    }

    component FormParametersSlider: RowLayout {
        property string description: "None"
        property string key: "--error"
        property int category: Net.Form
        property real defaultValue: 1
        property real min: 0
        property real max: 2
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: theme.text
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        Text {
            text: Number(__slider.value).toFixed(1)
            color: theme.yellow
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        Slider
        {
            id: __slider
            value: defaultValue
            from: min
            to: max
            onValueChanged: NetworkAPI.execd.setArgument(key, Number(value).toFixed(0), category)
        }
    }

    component Spacer: Item { Layout.fillHeight: true; height: 15 }
    component LargeSpacer: Item { Layout.fillHeight: true; height: 35 }

    ScrollView {
        id: scrollview
        Layout.fillHeight: true
        Layout.fillWidth: true
        implicitHeight: parent.height;
        implicitWidth: parent.width;
        clip: true;
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff;

        ColumnLayout {
            width: scrollview.width - 30;
            spacing: -5

            FormParametersDecimalInputWithInfo { description: "Ближняя граница РЛИ, м"; key: "--x0"; category: Net.Form; defaultValue: "100.0"; details: "Расстояние от БПЛА до ближнего края изображения" }
            FormParametersDecimalInputWithInfo { description: "Протяженность по дальности, м"; key: "--lx"; category: Net.Form; defaultValue: "2000.0"; details: "Расстояние от ближнего края изображения до дальнего края изображения" }
            FormParametersDecimalInputWithInfo { description: "Смещение кадра, м"; key: "--y0"; category: Net.Form; defaultValue: "0.0"; details: "Не используется в данной версии прошивки РЛС" }
            FormParametersDecimalInputWithInfo { description: "Протяженность по путевой дальности, м"; key: "--ly"; category: Net.Form; defaultValue: "400.0"; details: "Не используется в данной версии прошивки РЛС" }
            FormParametersDualDecimalInput { description: "Элемент разрешения, м"; firstKey: "--dx"; secondKey: "--dy"; category: Net.Form; defaultValue: "1.0"; details: "Количество метров в одном пикселе изображения" }

            LargeSpacer { }

            FormParametersSwitchableDecimalInput { description: "Яркость РЛИ"; key: "-b"; category: Net.Form; defaultValue: "0.0"; switched: false }
            FormParametersDecimalInput { description: "Время синтезирования, с"; key: "--Ts"; category: Net.Form; defaultValue: "1.0" }
            FormParametersDecimalInput { description: "Смещение по времени, с"; key: "-t"; category: Net.Form; defaultValue: "1.0" }

            LargeSpacer { }

            FormParametersSwitchableDecimalInput { description: "Высота БПЛА, м"; key: "-e"; category: Net.Form; defaultValue: "-1.0"; switched: false }
            FormParametersSwitchableDecimalInput { description: "Скорость БПЛА, км/ч"; key: "-v"; category: Net.Form; defaultValue: "-1.0"; switched: false }

            LargeSpacer { }

            FormParametersSlider { description: "Качество JPEG"; key: "--jq"; category: Net.Form; defaultValue: 80; min: 1; max: 100 }
            FormParametersSlider { description: "КЧИ по наклонной дальности"; key: "--kR"; category: Net.Form; defaultValue: 1; min: 0; max: 4 }
            FormParametersSlider { description: "КЧИ по путевой дальности"; key: "--kL"; category: Net.Form; defaultValue: 1; min: 0; max: 4 }
            RowLayout {
                Text {
                    Layout.fillWidth: true
                    text: "Тип вычислителя:"
                    color: theme.text
                    font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
                }

                ComboBox {
                    font {
                        family: root.mainfont
                        pixelSize: 14
                        weight: Font.Bold
                    }

                    currentIndex: 0;
                    model: [ "DSP_FFTW", "DSP_CUDA" ]
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    onCurrentValueChanged: NetworkAPI.execd.setArgument("--DSP", currentValue, Net.Form)
                }
            }
            FormParametersFilePathInput { description: "Путь к файлам на РЛС"; key: "--ip"; category: Net.Form; defaultValue: "./img/" }
            CheckBox {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                text: "Интерполяция скорости"
                checked: false
                font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
                onCheckedChanged: NetworkAPI.execd.setArgument("-i", (checked ? "1" : "0"), Net.Form)
            }

            CheckBox {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                text: "Отзеркаливание РЛИ"
                checked: false
                font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
                onCheckedChanged: NetworkAPI.execd.setArgument("--mirror", (checked ? "True" : "False"), Net.Form)
            }
        }
    }
}
