import QtQuick 2.12
import UX 1.0
import RuntimeData 1.0
import SignalLinker 1.0
import "qrc:/qml/ui/buttons" as Buttons

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
        display_mode: Buttons.ClassicButton.Mode.LabelOnly;
        anchors.bottom: parent.bottom;              anchors.bottomMargin: 14;
        anchors.left: parent.left;                  anchors.leftMargin: 8;
        fixed_width: 188;                           fixed_height: 28;
        label_text: "ФОРМИРОВАНИЕ РЛИ";     label_color: UX.textWhite;     label_text_size: 17;        
        label_text_family: fontBold.name;   label_text_bold: true;
        background_color: UX.infoLight;     background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: 
        { 
            SignalLinker.formSingleImage(); 
        }
    }
}
