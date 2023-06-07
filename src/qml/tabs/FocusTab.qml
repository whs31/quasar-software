import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Images 1.0
import Network 1.0

Rectangle { id: focustab_root;
    color: Theme.color("dark0");

    property int currentAssignedIndex: -1;
    onCurrentAssignedIndexChanged: {
        if(currentAssignedIndex >= 0)
            mapImage.source = "file:///" + ImagesModel.getRole(currentAssignedIndex, "filepath");
    }

    Connections {
        target: ImagesModel;
        function onTotalCountChanged()
        {
            currentAssignedIndex = -1;
        }
    }

    Flickable { id: flick;
        anchors.fill: parent;
        clip: true;

        Rectangle {
            id: rect;
            color: Theme.color("dark0");
            width: Math.max(mapImage.sourceSize.width, flick.width);
            height: Math.max(mapImage.sourceSize.height, flick.height);
            transform: Scale {
                id: scaler;
                origin.x: pinchArea.m_x2;
                origin.y: pinchArea.m_y2;
                xScale: pinchArea.m_zoom2;
                yScale: pinchArea.m_zoom2;
            }

            Image { id: mapImage;
                z: dragArea.z + 1;
                source: "qrc:/map/patterns/diagonal.png";
                anchors.centerIn: parent;
                fillMode: Image.PreserveAspectFit;
            }

            PinchArea { id: pinchArea;
                anchors.fill: parent;
                property real m_x1: 0;
                property real m_y1: 0;
                property real m_y2: 0;
                property real m_x2: 0;
                property real m_zoom1: 0.5;
                property real m_zoom2: 0.5;
                property real m_max: 2;
                property real m_min: 0.5;

                onPinchStarted: {
                    m_x1 = scaler.origin.x;
                    m_y1 = scaler.origin.y;
                    m_x2 = pinch.startCenter.x;
                    m_y2 = pinch.startCenter.y;
                    rect.x = rect.x + (pinchArea.m_x1 - pinchArea.m_x2) * (1 - pinchArea.m_zoom1);
                    rect.y = rect.y + (pinchArea.m_y1 - pinchArea.m_y2) * (1 - pinchArea.m_zoom1);
                }
                onPinchUpdated: {
                    m_zoom1 = scaler.xScale;
                    var dz = pinch.scale - pinch.previousScale;
                    var newZoom = m_zoom1 + dz;
                    if(newZoom <= m_max && newZoom >= m_min)
                        m_zoom2 = newZoom;
                }
                MouseArea { id: dragArea;
                    hoverEnabled: true;
                    anchors.fill: parent;
                    drag.target: rect;
                    drag.filterChildren: true;

                    onWheel: {
                        pinchArea.m_x1 = scaler.origin.x;
                        pinchArea.m_y1 = scaler.origin.y;
                        pinchArea.m_zoom1 = scaler.xScale;
                        pinchArea.m_x2 = mouseX;
                        pinchArea.m_y2 = mouseY;

                        var newZoom;
                        if(wheel.angleDelta.y > 0)
                        {
                            newZoom = pinchArea.m_zoom1 + 0.1;
                            if(newZoom <= pinchArea.m_max)
                                pinchArea.m_zoom2 = newZoom;
                            else
                                pinchArea.m_zoom2 = pinchArea.m_max;
                        }
                        else
                        {
                            newZoom = pinchArea.m_zoom1-0.1
                            if(newZoom >= pinchArea.m_min)
                                pinchArea.m_zoom2 = newZoom
                            else
                                pinchArea.m_zoom2 = pinchArea.m_min
                        }
                        rect.x = rect.x + (pinchArea.m_x1 - pinchArea.m_x2) * (1 - pinchArea.m_zoom1);
                        rect.y = rect.y + (pinchArea.m_y1 - pinchArea.m_y2) * (1 - pinchArea.m_zoom1);
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: console.log("Click in child")
                    }
                }
            }
        }
    }
}
