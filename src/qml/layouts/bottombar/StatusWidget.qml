import QtQuick 2.15
import Theme 1.0
import Widgets.Status 1.0

Item {
    enum ConnectionStatus {
        Unconnected,
        SemiConnected,
        Connected
    }

    property int i_ConnectionStatus: StatusWidget.ConnectionStatus.Unconnected;

    width: 312;
    height: 46;

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            i_ConnectionStatus = StatusWidget.ConnectionStatus.Connected; // replace to network access
        }
    }

    Rectangle {
        color: Theme.color("dark0");
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 7;
        height: 30;
        radius: 15;

        // interactive widget here
        StatusIndicator { id: c_Indicator;
            width: 20;
            height: 20;
            anchors.left: parent.left;
            anchors.leftMargin: 5;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -5;
            state: i_ConnectionStatus;
            errorColor: Theme.color("red");
            warnColor: Theme.color("orange");
            successColor: Theme.color("green");

            SequentialAnimation {
                NumberAnimation {
                    target: c_Indicator;
                    property: "opacity";
                    from: 0;
                    to: 1;
                    duration: 500;
                }
                NumberAnimation {
                    target: c_Indicator;
                    property: "opacity";
                    from: 1;
                    to: 0;
                    duration: 500;
                }
                loops: Animation.Infinite;
                running: true;
            }
        }

        Text {
            color: i_ConnectionStatus === StatusWidget.ConnectionStatus.Connected ? Theme.color("green") : Theme.color("red");
            font.weight: Font.ExtraBold;
            font.family: root.s_FontMain;
            font.pixelSize: 15;
            text: i_ConnectionStatus === StatusWidget.ConnectionStatus.Connected ? "ПОДКЛЮЧЕНО К РЛС" : "НЕТ ПОДКЛЮЧЕНИЯ К РЛС";
            width: 230;
            height: 26;
            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            anchors.leftMargin: 30;
        }
    }

    Rectangle {
        color: Theme.color("dark1");
        width: 111;
        height: 12;
        radius: 3;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;

        Text {
            anchors.centerIn: parent;
            text: "СТАТУС";
            font.family: root.s_FontMain;
            font.weight: Font.DemiBold;
            font.pixelSize: 10;
            color: Theme.color("light0");
        }
    }
}
