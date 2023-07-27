import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import QuaSAR.API 1.0

Pane {
    property bool shown: false

    height: shown ? implicitHeight : 0
    implicitHeight: 300
    visible: height > 0
    enabled: visible
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 150 } }
    clip: true
    opacity: 0.75
    Material.elevation: 30
    Material.accent: ColorTheme.active.color(ColorTheme.Yellow)
    Material.background: ColorTheme.active.color(ColorTheme.Dark)

    component FormParametersDecimalInput: RowLayout {
        property string description: "None"
        property string key: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        TextField {
            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: NetworkAPI.setArgument(key, text, category)
        }
    }

    component FormParametersDualDecimalInput: RowLayout {
        property string description: "None"
        property string firstKey: "--error"
        property string secondKey: "--error"
        property int category: Net.Form
        property string defaultValue: "error"
        opacity: enabled ? 1 : 0.4

        Text {
            Layout.fillWidth: true
            text: description + ":"
            color: ColorTheme.active.color(ColorTheme.Text)
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
        }

        TextField {
            validator: RegExpValidator { regExp: /^[0-9]*(\.[0-9]{0,2})?$/ }
            selectByMouse: true
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            text: defaultValue
            font { family: root.mainfont; weight: Font.Bold; pixelSize: 14 }
            onEditingFinished: {
                NetworkAPI.setArgument(firstKey, text, category)
                NetworkAPI.setArgument(secondKey, text, category)
            }
        }
    }

    component ConfigCheckbox: CheckBox {
        id: comp
        property string description: "None"
        property string key: "null/null"
        property alias isChecked: comp.checked
        Layout.fillWidth: true
        text: description
        checked: Settings.io.parameter(key)
        font { family: root.mainfont; weight: Font.DemiBold; pixelSize: 14 }
        onCheckedChanged: Settings.setParameter(key, checked)
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

            FormParametersDecimalInput { description: "Ближняя граница РЛИ, м"; key: "--x0"; category: Net.Form; defaultValue: "100.0" }
            FormParametersDecimalInput { description: "Протяженность по дальности, м"; key: "--lx"; category: Net.Form; defaultValue: "2000.0" }
            FormParametersDecimalInput { description: "Смещение кадра, м"; key: "--y0"; category: Net.Form; defaultValue: "0.0" }
            FormParametersDecimalInput { description: "Протяженность по путевой дальности, м"; key: "--ly"; category: Net.Form; defaultValue: "400.0" }
            FormParametersDualDecimalInput { description: "Элемент разрешения, м"; firstKey: "--dx"; secondKey: "--dy"; category: Net.Form; defaultValue: "1.0" }
        }
    }
}
