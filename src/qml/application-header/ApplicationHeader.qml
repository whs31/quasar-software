import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import "qrc:/qml/ui" as UI
import ApplicationHeader 1.0

Rectangle {
    id: base;
    width: 256; height: 70;
    color: "#293133";

    ApplicationHeader { id: applicationHeader; }

    UI.ClassicButton
    {
        id: closeButton;
        display_mode: ClassicButton.Mode.IconOnly;
        anchors.top: parent.top;            anchors.topMargin: 6;
        anchors.right: parent.right;        anchors.rightMargin: 6;
        fixed_width: 47;            fixed_height: 27;
        icon_px_size: 15;           icon_source: "qrc:/ui-resources/white/close.png";
        background_color: "#B16573";
        background_secondary_color: Qt.lighter(background_color, 1.5); 
        background_radius: 2;
        onClicked: { applicationHeader.close(); }
    }
}
