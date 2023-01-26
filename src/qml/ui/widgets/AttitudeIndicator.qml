import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import "qrc:/qml/ui" as UI
import RuntimeData 1.0
import QtGraphicalEffects 1.15
import DynamicResolution 1.0
import UX 1.0

Rectangle {
    id: base;
    color: UX.textWhite;
    width: 280 * DynamicResolution.kw;
    height: 160 * DynamicResolution.kh ;
    opacity: 1;
    radius: 6 * DynamicResolution.kw;
    border.width: 2 * DynamicResolution.kh;
    border.color: UX.textFaded;
    clip: true;
    Rectangle
    {
        id: indicator;
        anchors.fill: parent;
        color: UX.errorDark;
        border.width: 2;
        border.color: UX.textWhite;
        rotation: -RuntimeData.roll;
        visible: true;
        Rectangle
        {
            id: top;
            color: UX.textFaded;
            border.width: 1;
            border.color: UX.textWhite;
            anchors.bottom: parent.verticalCenter;
            anchors.top: parent.top;
            anchors.topMargin: -100 * DynamicResolution.kh;
            anchors.left: parent.left;
            anchors.leftMargin: -50 * DynamicResolution.kw;
            anchors.right: parent.right;
            anchors.rightMargin: -50 * DynamicResolution.kw;
            anchors.margins: 2;
            anchors.bottomMargin: -90 * Math.sin(RuntimeData.pitch * 3.14 / 180);
            Image { id: scaleTop; opacity: 0.9; width: 34 * DynamicResolution.kw;
                    height: 180 * DynamicResolution.kh; source: "qrc:/map-resources/attitude-indicator/scale-vertical.png";
                    smooth: true; antialiasing: true; anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter;  }
        }
        Rectangle
        {
            id: bottom;
            color: UX.primaryDarker;
            border.width: 1;
            border.color: UX.textWhite;
            anchors.top: parent.verticalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: -100 * DynamicResolution.kh;
            anchors.left: parent.left;
            anchors.leftMargin: -50 * DynamicResolution.kw;
            anchors.right: parent.right;
            anchors.rightMargin: -50 * DynamicResolution.kw;
            anchors.margins: 2;
            anchors.topMargin: 90 * Math.sin(RuntimeData.pitch * 3.14 / 180);
            //clip: true;
            Image { id: scaleBottom; opacity: 0.9; width: 34 * DynamicResolution.kw;
                    height: 180 * DynamicResolution.kh; source: "qrc:/map-resources/attitude-indicator/scale-vertical.png";
                    smooth: true; antialiasing: true; anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter;  }
        }
    }

    // static parts
    Image { id: crosshair1; width: 70 * DynamicResolution.kw; height: 70 * DynamicResolution.kh; source: "qrc:/map-resources/attitude-indicator/crosshair-1.png";
            smooth: true; antialiasing: true; anchors.centerIn: parent; anchors.verticalCenterOffset: -1; }
    Image { id: crosshair2; width: 34 * DynamicResolution.kw; height: 34 * DynamicResolution.kh; source: "qrc:/map-resources/attitude-indicator/crosshair-2.png";
            smooth: true; antialiasing: true; anchors.centerIn: parent; anchors.verticalCenterOffset: -2; }
    Rectangle { id: dot; width: 4 * DynamicResolution.kw; height: 4 * DynamicResolution.kh; radius: 2 * DynamicResolution.kw;
                anchors.centerIn: parent; smooth: true; antialiasing: true; }
    Rectangle { id: leftArm; height: 1 * DynamicResolution.kh; anchors.left: parent.left; anchors.right: crosshair1.left; anchors.verticalCenter:
                parent.verticalCenter; color: UX.textWhite; }
    Rectangle { id: rightArm; height: 1 * DynamicResolution.kh; anchors.left: crosshair1.right; anchors.right: parent.right; anchors.verticalCenter:
                parent.verticalCenter; color: UX.textWhite; }
}
