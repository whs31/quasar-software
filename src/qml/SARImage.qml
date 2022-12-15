import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.15


MapQuickItem {
//    function remove()
//    {
//        console.log(index);
//        //индекс становится равным -1 после вызова remove(index).
//        //сначала мы делаем все действия в бэкэнде, и только после этого убираем маркер из модели
//        markerRemove(index);
//        markerModel.remove(index);
//    }
    id: sarimage;
    anchorPoint.x: -m_x0;
    anchorPoint.y: m_height / 2;
    z: 2;
    zoomLevel: m_zoom;
    property real m_opacity: 1;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(m_lat, m_lon);
    sourceItem: Item {
        Image {
            id: imageSource;
            layer.enabled: true;
            transform: Rotation {
                id: imageRotation;
                origin.x: -m_x0;
                origin.y: m_height / 2;
                angle: m_angle;
            }
            smooth: true;
            source: "data:image/png;base64," + m_base64;
            visible: true;
            DropShadow {
                anchors.fill: imageSource;
                horizontalOffset: 50;
                verticalOffset: 50;
                radius: 8.0;
                samples: 17;
                color: "#000000";
                source: imageSource;
            }
        }
//        MouseArea {
//                id: sarMouseArea;
//                propagateComposedEvents: true;
//                anchors.left: imageSource.left;
//                anchors.leftMargin: -5;
//                anchors.right: imageSource.right;
//                anchors.rightMargin: -5;
//                anchors.bottom: imageSource.bottom;
//                anchors.bottomMargin: -5;
//                anchors.top: imageSource.top;
//                anchors.topMargin: -5;
//                hoverEnabled: true;
//                transform: Rotation {
//                    id: areaRotation;
//                    origin.x: -m_x0;
//                    origin.y: m_height / 2;
//                    angle: m_angle;
//                }
//                onEntered: {
//                    //imageUIModel.get(index).sardialogFadeIn.start();
//                    imageUIModel.set(index, {visible: true});
//                    //imageUIModel.setProperty(index, "enabled", true);
//                    console.log(index);
//                }
//                onExited: {
//                    //imageUIModel.get(index).sardialogFadeOut.start();
//                    imageUIModel.set(index, {visible: true});
//                    //imageUIModel.setProperty(index, "enabled", false);
//                    console.log(index);
//                }
//            }
    }
}

