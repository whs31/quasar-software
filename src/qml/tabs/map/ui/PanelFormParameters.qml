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
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 300 } }
    clip: true
    opacity: 0.75
    Material.elevation: 30
    Material.background: ColorTheme.active.color(ColorTheme.Dark)
}
