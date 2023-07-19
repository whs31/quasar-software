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
    anchorPoint.y: height
    coordinate: NetworkAPI.telemetry.position
    z: 19

    Behavior on coordinate { CoordinateAnimation { duration: 125; easing.type: Easing.Linear; } }

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
        Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }

        ListView {
            add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 1000; } }
            remove: Transition { NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 1000; } }
            model: NotificationsModel
            delegate: RowLayout {
                required property int index
                required property int level
                required property string message

                RoundButton {
                    flat: true
                    icon.source: "qrc:/icons/vector/common/warning.svg"
                    icon.color: level === NotificationsModel.Alert ? ColorTheme.active.color(ColorTheme.Red)
                                                                   : ColorTheme.active.color(ColorTheme.Orange)
                }

                Text {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font {
                        pixelSize: 14
                        weight: Font.ExtraBold
                        capitalization: Font.AllUppercase
                    }

                    text: message
                    color: level === NotificationsModel.Alert ? ColorTheme.active.color(ColorTheme.Red)
                                                              : ColorTheme.active.color(ColorTheme.Orange)
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
