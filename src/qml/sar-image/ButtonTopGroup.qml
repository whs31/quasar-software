import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import UX 1.0

RowLayout {
    property bool mainImageVisibleState: true;
    spacing: 1;
    RoundButton {
        id: hideButton
        radius: 4
        icon.cache: true
        hoverEnabled: true;
        scale: 1
        z: 100
        display: AbstractButton.IconOnly
        icon.color: UX.textWhite;
        icon.source: "qrc:/ui-resources/white/hide.png"
        icon.width: 30;
        icon.height: 30;
        Layout.preferredWidth: 40;
        Layout.preferredHeight: 40;
        onClicked: {
            mainImageVisibleState = !mainImageVisibleState;
            imageModel.setProperty(index, "m_i_visible", mainImageVisibleState);
        }
    }
    RoundButton {
        id: deleteButton;
        radius: 4;
        icon.cache: true;
        Material.background: UX.errorDark;
        hoverEnabled: true;
        scale: 1;
        z: 100;
        display: AbstractButton.IconOnly;
        icon.color: UX.textWhite;
        icon.source: "qrc:/ui-resources/white/trashbin.png";
        icon.width: 30;
        icon.height: 30;
        Layout.preferredWidth: 40;
        Layout.preferredHeight: 40;
        onClicked: {
            remove();
        }
    }
}
