import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15
import Theme 1.0
import Config 1.0

Pane {
    property bool b_Shown: false;
    width: b_Shown ? implicitWidth : 0;
    height: b_Shown ? implicitHeight : 0;
    visible: height > 0;
    enabled: visible;
    Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad; } }
    clip: true;

    Material.background: ColorTheme.active.color(ColorTheme.Dark)
    Material.elevation: 200

    layer.enabled: true
    layer.effect: DropShadow {
        samples: 16
        radius: 16
        horizontalOffset: 6
        verticalOffset: 6
        opacity: 0.5
    }

    implicitWidth: 350;
    implicitHeight: 500;

    Image { id: image_Logo;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        width: 300;
        height: 150;
        fillMode: Image.PreserveAspectFit;
        smooth: true;
        antialiasing: true;
        source: "qrc:/logo/logo_label.svg";
        mipmap: true;
    }

    Text {
        text: "Версия " + Config.projectVersion();
        font.family: root.mainfont;
        font.bold: true;
        font.pixelSize: 22;
        color: ColorTheme.active.color(ColorTheme.Yellow)
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: image_Logo.bottom;
    }

    Row { id: layout_Logos;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: image_Logo.bottom;
        anchors.topMargin: 180;

        Image {
            width: 200;
            height: 100;
            fillMode: Image.PreserveAspectFit;
            smooth: true;
            antialiasing: true;
            source: "qrc:/logo/radar-mms_white.png";
            mipmap: true;

            MouseArea {
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor;
                onClicked: Qt.openUrlExternally("https://radar-mms.com");
            }
        }

        Image {
            width: 200;
            height: 100;
            fillMode: Image.PreserveAspectFit;
            smooth: true;
            antialiasing: true;
            source: "qrc:/logo/gitlab.png";
            mipmap: true;

            MouseArea {
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor;
                onClicked: Qt.openUrlExternally("http://uav.radar-mms.com/gitlab/developers/rls/quasar");
            }
        }
    }

    RoundButton { id: button_CloseInfoWindow;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        width: 200;
        font.family: root.mainfont;
        font.weight: Font.Bold;
        height: 44;
        radius: 4;
        Material.elevation: 30;
        Material.background: ColorTheme.active.color(ColorTheme.Dark)
        text: "Закрыть";
        onPressed: b_Shown = false;
    }
}
