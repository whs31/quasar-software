import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import "qrc:/qml/ui/buttons" as Buttons
import ApplicationHeader 1.0

Rectangle {
    id: base;
    width: 256; height: 70;
    color: "#293133";

    ApplicationHeader { id: applicationHeader; }

    Buttons.ClassicButton
    {
        id: closeButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: parent.top;            anchors.topMargin: 6;
        anchors.right: parent.right;        anchors.rightMargin: 6;
        fixed_width: 47;            fixed_height: 27;
        icon_px_size: 15;           icon_source: "qrc:/icons/close.png";
        background_color: "#B16573";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.close(); }
    }
    Buttons.ClassicButton
    {
        id: minimizeButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: closeButton.top;            
        anchors.right: closeButton.left;        
        fixed_width: 47;            fixed_height: 27;
        icon_px_size: 15;           icon_source: "qrc:/icons/minus.png";
        background_color: "#293133";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.minimize(); }
    }
    Buttons.ClassicButton
    {
        id: emulatorButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: closeButton.top;            
        anchors.left: parent.left;      anchors.leftMargin: 6;    
        fixed_width: 27;            fixed_height: 27;
        icon_px_size: 16;           icon_source: "qrc:/icons/debug.png";
        background_color: "#293133";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.emulator(); }
    }
    Buttons.ClassicButton
    {
        id: debugButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: closeButton.top;            
        anchors.left: emulatorButton.right;      
        fixed_width: 27;            fixed_height: 27;
        icon_px_size: 21;           icon_source: "qrc:/icons/command-line.png";
        background_color: "#293133";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.log(); }
    }
    Buttons.ClassicButton
    {
        id: settingsButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: closeButton.top;            
        anchors.left: debugButton.right;      anchors.leftMargin: 6;    
        fixed_width: 27;            fixed_height: 27;
        icon_px_size: 18;           icon_source: "qrc:/icons/settings.png";
        background_color: "#293133";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.settings(); }
    }
    Buttons.ClassicButton
    {
        id: infoButton;
        display_mode: Buttons.ClassicButton.Mode.IconOnly;
        anchors.top: closeButton.top;            
        anchors.left: settingsButton.right;       
        fixed_width: 27;            fixed_height: 27;
        icon_px_size: 18;           icon_source: "qrc:/icons/info.png";
        background_color: "#293133";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.info(); }
    }
}
