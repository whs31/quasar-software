import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import UX 1.0
import DialogWindowBackend 1.0
import RuntimeData 1.0

import "qrc:/qml/ui/buttons" as Buttons
import "qrc:/qml/ui/labels" as Labels

RowLayout {
    property bool mainImageVisibleState: true;
    spacing: 4;
    Buttons.LightToolButton
    {
        id: hideButton;
        fixed_width: 30;
        fixed_height: 30;
        frame_color: UX.textWhite;
        highlight_color: UX.infoLight;
        frame_radius: 8;
        frame_enabled: true;
        icon_px_size: 18;
        icon_source: "qrc:/ui-resources/white/hide.png";
        tooltip_text: "Показать/скрыть изображение";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
            mainImageVisibleState = !mainImageVisibleState;
            imageModel.setProperty(index, "m_i_visible", mainImageVisibleState);
        }
    }
    Buttons.LightToolButton
    {
        property bool waitingForDialogResponse: false;

        id: deleteButton;
        enabled: !RuntimeData.windowLock;
        fixed_width: 30;
        fixed_height: 30;
        frame_color: UX.textWhite;
        highlight_color: UX.errorDark;
        frame_radius: 8;
        frame_enabled: true;
        icon_px_size: 18;
        icon_source: "qrc:/ui-resources/white/trashbin.png";
        tooltip_text: "Показать/скрыть изображение";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
            RuntimeData.windowLock = true;
            DialogWindowBackend.header = "ОЧИСТКА КАРТЫ";
            DialogWindowBackend.icon = "qrc:/icons/dialog/warning.png";
            DialogWindowBackend.text = "Вы уверены, что хотите удалить это изображение с карты?";
            DialogWindowBackend.show();
            waitingForDialogResponse = true;
        }
        function handleResponse()
        {
            if(waitingForDialogResponse === true)
            {
                if(DialogWindowBackend.returnCode === 1)
                {
                    remove();
                    waitingForDialogResponse = false;
                }
            }
        }
        Component.onCompleted: {
            DialogWindowBackend.returnCodeChanged.connect(handleResponse)
        }
    }
}
