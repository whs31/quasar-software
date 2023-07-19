import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.15

import QuaSAR.API 1.0

import Theme 1.0
import Notifications 1.0

MapQuickItem {
    anchorPoint.x: width / 2
    anchorPoint.y: height + 20
    coordinate: NetworkAPI.telemetry.position
    z: 19
    visible: rpt.count > 0
    enabled: visible

    Behavior on coordinate { CoordinateAnimation { duration: 125; easing.type: Easing.Linear; } }
    Material.background: "#50181926" // @TODO use utils to convert it.

    sourceItem: Pane {
        clip: true
        layer.enabled: true
        layer.effect: DropShadow {
            samples: 16
            radius: 16
            horizontalOffset: 6
            verticalOffset: 6
            opacity: 0.5
        }
        Behavior on implicitHeight { NumberAnimation { easing.type: Easing.InOutQuad; duration: 500; } }
        Behavior on implicitWidth { NumberAnimation { easing.type: Easing.InOutQuad; duration: 500; } }

        ColumnLayout {
            Repeater {
                id: rpt
                model: NotificationsModel
                delegate: RoundButton {
                    required property int index
                    required property int level
                    required property string message

                    flat: true
                    icon.source: level === NotificationsModel.Alert ? "qrc:/icons/vector/common/error.svg"
                                                                    : "qrc:/icons/vector/common/warning.svg"
                    icon.color: level === NotificationsModel.Alert ? ColorTheme.active.color(ColorTheme.Red)
                                                                   : ColorTheme.active.color(ColorTheme.Orange)
                    Material.foreground: level === NotificationsModel.Alert ? ColorTheme.active.color(ColorTheme.Red)
                                                                            : ColorTheme.active.color(ColorTheme.Orange)

                    font {
                        pixelSize: 12
                        weight: Font.Bold
                        capitalization: Font.AllUppercase
                    }

                    text: message
                }
            }
        }
    }
}
