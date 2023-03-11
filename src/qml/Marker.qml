import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.15
import Theme 1.0
import "qrc:/qml/ui/widgets" as CustomWidgets


MapQuickItem {
    //anchors must be set according to 32x32 rescaled image
    //e.g. middle will be QPoint(16, 16);
    property bool removingTrigger: removeTrigger;
    onRemovingTriggerChanged: remove();

    function remove()
    {
        //индекс становится равным -1 после вызова remove(index). 
        //сначала мы делаем все действия в бэкэнде, и только после этого убираем маркер из модели
        markerRemove(index);
        markerModel.remove(index);
    }

	FontLoader { id: fnt; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }

    id: marker
    anchorPoint.x: anchorX;
    anchorPoint.y: anchorY;
    z: 2;
    zoomLevel: m_zoom;
    property real m_opacity: 1;
    opacity: m_opacity;
    coordinate: QtPositioning.coordinate(lat, lon);
    property alias markerName: markerText.text;
    sourceItem: Item {
        Image {
            id: markerSource;
            width: 32;
            height: 32;
            layer.enabled: true;
            transformOrigin: Item.Center;
            smooth: true;
            source: m_qrc;
            visible: true;
        }
        MouseArea {
                id: markerMouseArea;
                propagateComposedEvents: true;
                anchors.left: markerSource.left;
                anchors.leftMargin: -5;
                anchors.right: markerSource.right;
                anchors.rightMargin: -5;
                anchors.bottom: markerSource.bottom;
                anchors.bottomMargin: -5;
                anchors.top: markerSource.top;
                anchors.topMargin: -20;
                hoverEnabled: true;
                onEntered: {
                    dialogFadeIn.start();
                    markerDialog.visible = true;
                    markerDialog.enabled = true;
                }
                onExited: {
                    dialogFadeOut.start();
                    markerDialog.enabled = false;
                }
            }
        ColorOverlay {
            id: markerOverlay;
            anchors.fill: markerSource;
            source: markerSource;
            opacity: 0.75;
            color: m_color;
        }
        DropShadow {
            anchors.fill: markerOverlay;
            horizontalOffset: 5;
            verticalOffset: 5;
            radius: 8.0;
            samples: 17;
            color: Theme.color("dark1");
            source: markerOverlay;
        }
        Rectangle {
            id: textOverlay;
            color: markerOverlay.color;
            width: markerText.paintedWidth + 10;
            height: markerText.paintedHeight + 3;
            anchors.top: markerSource.bottom;
            anchors.topMargin: 5;
            anchors.horizontalCenter: markerSource.horizontalCenter;
            radius: 10
            Text {
                id: markerText;
                color: Theme.color("dark1");
                enabled: true;
                anchors.fill: parent;
				font.pointSize: 9;
				font.family: fnt.name;
                font.weight: Font.Bold;
                textFormat: Text.RichText;
				font.capitalization: Font.AllUppercase;
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
                text: m_name;
            }
        }
        CustomWidgets.InlineDialog {
            id: markerDialog;
            opacity: 0;
            enabled: false;
            visible: false;
            anchors.bottom: markerSource.top;
            anchors.bottomMargin: 2;
            anchors.horizontalCenter: markerSource.horizontalCenter;
            NumberAnimation on opacity {
                id: dialogFadeIn;
                from: 0;
                to: 1;
                duration: 300;
                easing.type: Easing.Linear;
            }
            NumberAnimation on opacity {
                id: dialogFadeOut;
                from: 1;
                to: 0;
                duration: 300;
                easing.type: Easing.Linear;
            }
        }
    }
}
