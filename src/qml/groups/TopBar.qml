import QtQuick 2.12
import UX 1.0
import RuntimeData 1.0
import SignalLinker 1.0
import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels
import "qrc:/qml/ui/dropdowns" as Dropdowns

Rectangle {
    id: base;
    height: 70;
    color: UX.primaryDark;
    
    FontLoader { id: fontRegular; source: "qrc:/fonts/SofiaSans-Regular.ttf" }
    FontLoader { id: fontMedium; source: "qrc:/fonts/SofiaSans-Medium.ttf" }
    FontLoader { id: fontSemiBold; source: "qrc:/fonts/SofiaSans-SemiBold.ttf" }
    FontLoader { id: fontBold; source: "qrc:/fonts/SofiaSans-Bold.ttf" }
    FontLoader { id: fontExtraBold; source: "qrc:/fonts/SofiaSans-ExtraBold.ttf" }

    Buttons.ClassicButton
    {
        id: formImageButton;
        anchors.bottom: parent.bottom;              anchors.bottomMargin: 14;
        anchors.left: parent.left;                  anchors.leftMargin: 8;

        display_mode: Buttons.ClassicButton.Mode.LabelOnly;
        fixed_width: 188;                           fixed_height: 28;
        label_text: "ФОРМИРОВАНИЕ РЛИ";     
        label_color: UX.textWhite;          label_text_size: 17;        
        label_text_family: fontBold.name;   label_text_bold: true;
        background_color: UX.infoLight;     background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: 
        { 
            SignalLinker.formSingleImage(); 
        }
    }
    Labels.FramedLabel
    {
        id: formModeLabel;
        anchors.bottom: formImageButton.top;    anchors.bottomMargin: 4;
        anchors.left: formImageButton.left;

        fixed_width: 51;    fixed_height: 17;
        label_text: "РЕЖИМ";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignHCenter;
        frame_radius: 2;                    frame_width: 1;
    }
    Dropdowns.Dropdown
    {
        id: formModeDropDown;
        anchors.left: formModeLabel.right;  anchors.leftMargin: 1;
        anchors.top: formModeLabel.top;
        
        fixed_width: 136;       fixed_height: 17;           fixed_drop: 17*2;
        label_text: "ОДИНОЧНОЕ";
        label_color: UX.textWhite;          label_text_size: 12;
        label_text_family: fontMedium.name; label_text_bold: true;
        label_textAlignment: Text.AlignRight;
        highlight_color: UX.infoLight;
        frame_radius: 2;                    frame_width: 1;
        container: Rectangle { color: "#FF0000"; width: 50; height: 20; anchors.centerIn: parent; }
    }
}
