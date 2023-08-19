import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

MapQuickItem {
    property real m_opacity: transparency
    opacity: m_opacity
    z: 2
    visible: shown

    // image_type = 1  - полосовое.

    // точка привязки
    anchorPoint.x: -x0
    anchorPoint.y: image_type === 1 ? ly : ly / 2

    zoomLevel: mercator_zoom_level
    coordinate: QtPositioning.coordinate(latitude, longitude)

    sourceItem: Item {
        Loader {
            active: maptab_root.zoomLevel > 15 ||
                    maptab_root.visibleRegion.contains(QtPositioning.coordinate(latitude, longitude));
            asynchronous: true

            property var neural: neural_data

            sourceComponent: Image {
                layer {
                    enabled: true
                    smooth: true
                    samples: 8
                }
                asynchronous: true

                // точка вращения
                transform: Rotation {
                    property real corrected_drift_angle: (image_type === 0) ? drift_angle : 0

                    origin.x: -x0
                    origin.y: image_type === 1 ? ly : ly / 2
                    angle: model.angle + corrected_drift_angle
                }

                smooth: true
                antialiasing: true
                source: "file:///" + lod0

                Repeater {
                    model: neural
                    delegate: Rectangle {
                        required property var modelData
                        property rect box: modelData.rect
                        onBoxChanged: console.log("$ [NEURAL] Neural data received by QML: " + box)

                        color: "transparent"
                        border {
                            width: 4
                            color: modelData.color
                        }
                        width: Math.abs(box.right - box.left)
                        height: Math.abs(box.top - box.bottom)
                        x: box.left
                        y: box.top
                    }
                }
            }
        }
    }
}
