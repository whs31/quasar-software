import QtQuick 2.15
import UX 1.0
import RuntimeData 1.0
import Config 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels

Rectangle {
    id: window;
    opacity: RuntimeData.infoWindow ? 1.0 : 0;
    enabled: RuntimeData.infoWindow;
    height: 334;
    width: 294;
    radius: 35;
    color: UX.primaryDarker;
    Behavior on opacity { NumberAnimation { duration: 250; } }

    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }
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
