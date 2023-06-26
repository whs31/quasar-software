import QtQuick 2.15

import Theme 1.0
import Network 1.0

Item {
    enum ConnectionStatus {
        Unconnected,
        SemiConnected,
        Connected
    }

    property int i_ConnectionStatus: Network.connected;

    width: 312;
    height: 46;

    Rectangle {
        color: ColorTheme.active.color(ColorTheme.Dark)
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 7;
        height: 30;
        radius: 15;

        Rectangle { id: c_Indicator;
            width: 10;
            height: 10;
            radius: 3;
            anchors.left: parent.left;
            anchors.leftMargin: 12;
            anchors.verticalCenter: parent.verticalCenter;
            color: i_ConnectionStatus === StatusWidget.ConnectionStatus.Connected ? ColorTheme.active.color(ColorTheme.Green)
                                                                                  : ColorTheme.active.color(ColorTheme.Red)

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
            color: i_ConnectionStatus === StatusWidget.ConnectionStatus.Connected ? ColorTheme.active.color(ColorTheme.Green)
                                                                                  : ColorTheme.active.color(ColorTheme.Red)
            font.weight: Font.ExtraBold;
            font.family: root.mainfont;
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
        color: ColorTheme.active.color(ColorTheme.BaseShade)
        width: 111;
        height: 12;
        radius: 3;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;

        Text {
            anchors.centerIn: parent;
            text: "СТАТУС";
            font.family: root.mainfont;
            font.weight: Font.DemiBold;
            font.pixelSize: 10;
            color: ColorTheme.active.color(ColorTheme.Text)
        }
    }
}
