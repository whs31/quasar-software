import QtQuick 2.15
import QtLocation 5.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtPositioning 5.15
import Qt5Compat.GraphicalEffects

import Markers 1.0
import Theme 1.0

MapQuickItem {
    required property int index
    required property var markerCoordinate
    required property string markerName
    required property color markerColor
    required property string markerIcon

    property real m_opacity: 1

    anchorPoint.x: imageSource.sourceSize.width / 2
    anchorPoint.y: imageSource.sourceSize.height
    coordinate: markerCoordinate
    opacity: m_opacity
    visible: true
    z: 2
    zoomLevel: 0

    sourceItem: Item {
        Image {
            id: imageSource

            antialiasing: true
            asynchronous: true
            smooth: true
            source: markerIcon
            sourceSize.height: 40
            sourceSize.width: 40
            visible: false
        }

        ColorOverlay {
            anchors.fill: imageSource
            color: markerColor
            layer {
                enabled: true
                samples: 8
                smooth: true
            }
            source: imageSource
        }
        Rectangle {
            id: panel_MarkerTooltip

            anchors.horizontalCenter: imageSource.horizontalCenter
            anchors.top: imageSource.bottom
            anchors.topMargin: 4
            color: markerColor
            height: (text_MarkerName.paintedHeight + 1)
            radius: width / 2
            width: (text_MarkerName.paintedWidth + 5)

            Text {
                id: text_MarkerName

                anchors.fill: parent
                color: "black"
                enabled: true
                font.family: root.mainfont
                font.pointSize: 8
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignHCenter
                text: "\u00A0" + markerName + "\u00A0"
                textFormat: Text.RichText
                verticalAlignment: Text.AlignVCenter
            }
        }
        MouseArea {
            id: markermousearea

            property bool showcontrols: false

            anchors.fill: imageSource
            anchors.topMargin: -50
            hoverEnabled: true
            propagateComposedEvents: true

            onPressed: showcontrols = !showcontrols
        }

        RoundButton {
            Material.background: ColorTheme.active.color(ColorTheme.Red)
            height: 36
            icon.color: ColorTheme.active.color(ColorTheme.Dark)
            icon.source: "qrc:/icons/vector/common/close.svg"
            opacity: markermousearea.showcontrols ? 1 : 0
            width: 36

            Behavior on opacity  {
                NumberAnimation {
                    duration: 150
                }
            }

            onPressed: MarkersModel.remove(index)

            anchors {
                bottom: imageSource.top
                bottomMargin: 5
                horizontalCenter: imageSource.horizontalCenter
            }
        }
    }
}
