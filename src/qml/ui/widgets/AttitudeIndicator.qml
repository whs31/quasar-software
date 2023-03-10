import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtGraphicalEffects 1.15

import Theme 1.0
import Telemetry 1.0

import "qrc:/qml/ui" as UI

Rectangle {
    id: base;
	color: Theme.color("light1");
	width: 200 * Theme.scalingFactor.x;
	height: 110 * Theme.scalingFactor.y ;
    opacity: 1;
    radius: 6 * Theme.scalingFactor.x;
    border.width: 2 * Theme.scalingFactor.y;
	border.color: Theme.color("light0");
	clip: true;
    Rectangle
    {
        id: indicator;
        anchors.fill: parent;
		color: Theme.color("red");
        border.width: 2;
		border.color: Theme.color("light1");
        rotation: -Telemetry.roll;
        visible: true;
        Rectangle
        {
            id: top;
			color: Qt.darker(Theme.color("light0"), 1.3);
            border.width: 1;
			border.color: Theme.color("light1");
            anchors.bottom: parent.verticalCenter;
            anchors.top: parent.top;
            anchors.topMargin: -100 * Theme.scalingFactor.y;
            anchors.left: parent.left;
            anchors.leftMargin: -50 * Theme.scalingFactor.x;
            anchors.right: parent.right;
            anchors.rightMargin: -50 * Theme.scalingFactor.x;
            anchors.margins: 2;
            anchors.bottomMargin: -90 * Math.sin(Telemetry.pitch * 3.14 / 180);
            Image { id: scaleTop; opacity: 0.9; width: 34 * Theme.scalingFactor.x;
                    height: 180 * Theme.scalingFactor.y; source: "qrc:/attitude/scale-vertical.png";
                    smooth: true; antialiasing: true; anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter;  }
        }
        Rectangle
        {
            id: bottom;
			color: Theme.color("dark1");
            border.width: 1;
			border.color: Theme.color("light1");
            anchors.top: parent.verticalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: -100 * Theme.scalingFactor.y;
            anchors.left: parent.left;
            anchors.leftMargin: -50 * Theme.scalingFactor.x;
            anchors.right: parent.right;
            anchors.rightMargin: -50 * Theme.scalingFactor.x;
            anchors.margins: 2;
            anchors.topMargin: 90 * Math.sin(Telemetry.pitch * 3.14 / 180);
            //clip: true;
            Image { id: scaleBottom; opacity: 0.9; width: 34 * Theme.scalingFactor.x;
                    height: 180 * Theme.scalingFactor.y; source: "qrc:/attitude/scale-vertical.png";
                    smooth: true; antialiasing: true; anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter;  }
        }
    }

    // static parts
    Image { id: crosshair1; width: 70 * Theme.scalingFactor.x; height: 70 * Theme.scalingFactor.y; source: "qrc:/attitude/crosshair-1.png";
            smooth: true; antialiasing: true; anchors.centerIn: parent; anchors.verticalCenterOffset: -1; }
    Image { id: crosshair2; width: 34 * Theme.scalingFactor.x; height: 34 * Theme.scalingFactor.y; source: "qrc:/attitude/crosshair-2.png";
            smooth: true; antialiasing: true; anchors.centerIn: parent; anchors.verticalCenterOffset: -2; }
    Rectangle { id: dot; width: 4 * Theme.scalingFactor.x; height: 4 * Theme.scalingFactor.y; radius: 2 * Theme.scalingFactor.x;
                anchors.centerIn: parent; smooth: true; antialiasing: true; }
    Rectangle { id: leftArm; height: 1 * Theme.scalingFactor.y; anchors.left: parent.left; anchors.right: crosshair1.left; anchors.verticalCenter:
				parent.verticalCenter; color: Theme.color("light1"); }
    Rectangle { id: rightArm; height: 1 * Theme.scalingFactor.y; anchors.left: crosshair1.right; anchors.right: parent.right; anchors.verticalCenter:
				parent.verticalCenter; color: Theme.color("light1"); }
}
