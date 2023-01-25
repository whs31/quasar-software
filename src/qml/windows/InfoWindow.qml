import QtQuick 2.15
import UX 1.0
import RuntimeData 1.0
import Config 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels

Rectangle {
    id: window;
    visible: width > 0;
    enabled: RuntimeData.infoWindow;
    height: RuntimeData.infoWindow ? 334 : 0;
    width: RuntimeData.infoWindow ? 294 : 0;
    radius: 35;
    color: UX.primaryDarker;
    Behavior on width { NumberAnimation { duration: 250; easing.type: Easing.InOutCubic; } }
    Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutCubic; } }

    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
    Item {
        id: content;
        anchors.fill: parent;
        visible: RuntimeData.infoWindow;
        opacity: RuntimeData.infoWindow ? 1 : 0;
        Behavior on opacity { NumberAnimation { duration: 350; easing.type: Easing.InOutCubic; } }
        Image {
            id: quasarLogo;
            source: "qrc:/logo/full-logo_shadow.png";
            fillMode: Image.PreserveAspectFit;
            width: 276;
            height: 110;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 60;
            smooth: true;
            antialiasing: true;
            mipmap: true;
        }
        Labels.FramedLabel
        {
            id: statusBarTooltipLabel;
            anchors.bottom: quasarLogo.bottom;
            anchors.bottomMargin: 3;
            anchors.horizontalCenter: parent.horizontalCenter;
            fixed_width: 246;
            fixed_height: 24;
            label_text: Config.projectVersion;
            label_color: UX.textFaded;
            label_text_size: 18;
            label_text_family: fontExtraBold.name;
            label_text_bold: true;
            label_textAlignment: Text.AlignHCenter;
            frame_radius: 2;
            frame_width: 0;
        }
        Image {
            id: gitlabLogo;
            source: "qrc:/logo/gitlab.png";
            fillMode: Image.PreserveAspectFit;
            width: 125;
            height: 50;
            anchors.right: parent.horizontalCenter;
            anchors.bottom: closeInfoWindowButton.top;
            anchors.bottomMargin: 38;
            smooth: true;
            antialiasing: true;
            mipmap: true;
            MouseArea {
                id: mouseArea1;
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor;
                onClicked: Qt.openUrlExternally("http://uav.radar-mms.com/gitlab/developers/rls/quasar");
            }
        }
        Image {
            id: radarLogo;
            source: "qrc:/logo/radar-mms_white.png";
            fillMode: Image.PreserveAspectFit;
            width: 89;
            height: 66;
            anchors.left: parent.horizontalCenter; anchors.leftMargin: 20;
            anchors.bottom: closeInfoWindowButton.top;
            anchors.bottomMargin: 30;
            smooth: true;
            antialiasing: true;
            mipmap: true;
            MouseArea {
                id: mouseArea2;
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor;
                onClicked: Qt.openUrlExternally("https://radar-mms.com");
            }
        }
        Buttons.LightButton
        {
            id: closeInfoWindowButton;
            anchors.bottom: parent.bottom; anchors.bottomMargin: 12;
            anchors.horizontalCenter: parent.horizontalCenter;
            fixed_width: 103;               fixed_height: 20;
            label_text: "ЗАКРЫТЬ";
            label_color: UX.textWhite;  label_text_size: 14;
            label_text_family: fontBold.name;
            label_text_bold: true;         label_textAlignment: Text.AlignHCenter;
            highlight_color: UX.textFaded;
            frame_radius: 6;                frame_width: 1;
            frame_enabled: true;
            onClicked: {
                RuntimeData.infoWindow = false;
            }
        }
    }
}
