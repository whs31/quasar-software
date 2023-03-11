import QtQuick 2.15
import RuntimeData 1.0
import Config 1.0
import Theme 1.0
import QtGraphicalEffects 1.15
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels

Rectangle {
    id: window;
    visible: width > 0;
    enabled: RuntimeData.infoWindow;
    height: RuntimeData.infoWindow ? 334 * Theme.scalingFactor.x : 0;
    width: RuntimeData.infoWindow ? 294 * Theme.scalingFactor.y : 0;
    radius: 35;
    color: Theme.color("dark0");
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
            width: 276 * Theme.scalingFactor.x;
            height: 110 * Theme.scalingFactor.y;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 60 * Theme.scalingFactor.y;
            smooth: true;
            antialiasing: true;
            mipmap: true;
        }
        Labels.FramedLabel
        {
            id: statusBarTooltipLabel;
            anchors.bottom: quasarLogo.bottom;
            anchors.bottomMargin: 3 * Theme.scalingFactor.y;
            anchors.horizontalCenter: parent.horizontalCenter;
            fixed_width: 246 * Theme.scalingFactor.x;
            fixed_height: 24 * Theme.scalingFactor.y;
            label_text: "Версия 5.9.9beta";//Config.projectVersion;
            label_color: Theme.color("light0");
            label_text_size: 18 * Theme.scalingFactor.y;
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
            width: 125 * Theme.scalingFactor.x;
            height: 50 * Theme.scalingFactor.y;
            anchors.right: parent.horizontalCenter;
            anchors.bottom: closeInfoWindowButton.top;
            anchors.bottomMargin: 38 * Theme.scalingFactor.y;
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
            width: 89 * Theme.scalingFactor.x;
            height: 66 * Theme.scalingFactor.y;
            anchors.left: parent.horizontalCenter; anchors.leftMargin: 20;
            anchors.bottom: closeInfoWindowButton.top;
            anchors.bottomMargin: 30 * Theme.scalingFactor.y;
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
			anchors.bottom: parent.bottom;
			anchors.bottomMargin: 12 * Theme.scalingFactor.y;
            anchors.horizontalCenter: parent.horizontalCenter;
            fixed_width: 103 * Theme.scalingFactor.x;
            fixed_height: 20 * Theme.scalingFactor.y;
            label_text: "ЗАКРЫТЬ";
            label_color: Theme.color("light1");
            label_text_size: 14 * Theme.scalingFactor.y;
            label_text_family: fontBold.name;
            label_text_bold: true;
            label_textAlignment: Text.AlignHCenter;
            highlight_color: Theme.color("light0");
            frame_radius: 6;
            frame_width: 1 * Theme.scalingFactor.y;
            frame_enabled: true;
            onClicked: {
                RuntimeData.infoWindow = false;
                RuntimeData.windowLock = false;
            }
        }
    }
}
