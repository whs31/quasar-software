import QtQuick 2.12
import UX 1.0
import RuntimeData 1.0
import SignalLinker 1.0
import DiskManager 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns
import "qrc:/qml/ui/layouts" as Layouts
import "qrc:/qml/ui/widgets" as CustomWidgets

Rectangle {
    id: base;
    height: 36;
    color: UX.primaryDark;

    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }

    Labels.FramedLabel
    {
        id: satsLabel;
        anchors.bottom: parent.bottom;  anchors.bottomMargin: 8;
        anchors.right: parent.right; anchors.rightMargin: 5;

        fixed_width: 16;    fixed_height: 19;
        label_text: Number(RuntimeData.satellites);
        label_color: UX.textWhite;              label_text_size: 16;
        label_text_family: fontBold.name;   label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                        frame_width: 0;
    }
    Image {
        id: satsIcon;
        width: 22;
        height: 22;
        source: "qrc:/icons/satellite.png";
        smooth: true;
        antialiasing: true;
        anchors.right: satsLabel.left;  anchors.rightMargin: 2;
        anchors.verticalCenter: parent.verticalCenter;
    }

}
