import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Theme 1.0
import Config 1.0
import Filesystem 1.0

Pane { id: panel_ImageTools;
    property bool shown: false

    height: shown ? implicitHeight : 0
    visible: height > 0
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
    clip: true
    Material.elevation: 30

    ColumnLayout {
        RoundButton { id: button_ExportImages
            Layout.preferredHeight: 36
            font.family: root.mainfont
            height: 35
            radius: 4
            icon.source: "qrc:/icons/google-material/image.png"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            text: "Экспортировать выбранные изображения"
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            Layout.fillWidth: true
            onPressed: window_ExportDialog.open()
        }

        RoundButton { id: button_ExportMarkers;
            Layout.preferredHeight: 36
            font.family: root.mainfont
            height: 35
            radius: 4
            icon.source: "qrc:/icons/google-material/text.png"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            text: "Экспортировать маркеры в текст"
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            Layout.fillWidth: true
            enabled: false
        }

        RoundButton { id: button_ExportMarkersXML
            Layout.preferredHeight: 36
            font.family: root.mainfont
            height: 35
            radius: 4
            icon.source: "qrc:/icons/google-material/save.png"
            icon.color: ColorTheme.active.color(ColorTheme.Text)
            text: "Экспортировать маркеры в XML"
            Material.elevation: 30
            Material.background: ColorTheme.active.color(ColorTheme.BaseShade)
            Layout.fillWidth: true
            enabled: false
        }
    }
}
