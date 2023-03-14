import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import Theme 1.0
import DialogWindowBackend 1.0
import FocusWindowBackend 1.0
import RuntimeData 1.0

import SignalLinker 1.0
import FormParameters 1.0

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
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("color1");
        frame_radius: 8;
        frame_enabled: true;
        icon_px_size: 18;
        icon_source: "qrc:/icons/hide.png";
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

        id: focusButton;
        enabled: !RuntimeData.windowLock;
        fixed_width: 30;
        fixed_height: 30;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("color1");
        frame_radius: 8;
        frame_enabled: true;
        icon_px_size: 18;
        icon_source: "qrc:/icons/crosshair.png";
        tooltip_text: "Фокусировка изображения";
        tooltip_enabled: true;
        label_text_family: fontMedium.name;
        onClicked: {
            RuntimeData.windowLock = true;
            FocusWindowBackend.filename = m_filename;
            FocusWindowBackend.base64 = imageModel.get(index).m_base64;
            FocusWindowBackend.lx = imageModel.get(index).m_width;
            FocusWindowBackend.ly = imageModel.get(index).m_height;
            FocusWindowBackend.step = imageModel.get(index).m_dx;
            FocusWindowBackend.offset = imageModel.get(index).m_x0;
            FormParameters.reformVelocity = imageUIModel.get(index).m_velocity;
            FocusWindowBackend.show();
            waitingForDialogResponse = true;
        }
        function handleResponse()
        {
            if(waitingForDialogResponse === true)
            {
                if(FocusWindowBackend.returnCode === 1)
                {
                    //form parameters
                    FormParameters.focusX = FocusWindowBackend.x;
                    console.log(FormParameters.focusX)
                    FormParameters.focusY = FocusWindowBackend.y;
                    FormParameters.focusL = FocusWindowBackend.sideLength;
                    FormParameters.focusTime = FocusWindowBackend.time;
                    FormParameters.filename = FocusWindowBackend.filename;
                    SignalLinker.focus();
                    FormParameters.reformVelocity = -1;
                    waitingForDialogResponse = false;
                }
                else if(FocusWindowBackend.returnCode === 2)
                {
                    FormParameters.filename = FocusWindowBackend.filename;
                    SignalLinker.reform();
                    waitingForDialogResponse = false;
                }
            }
        }
        Component.onCompleted: {
            FocusWindowBackend.returnCodeChanged.connect(handleResponse)
        }
    }

    Buttons.LightToolButton
    {
        property bool waitingForDialogResponse: false;

        id: deleteButton;
        enabled: !RuntimeData.windowLock;
        fixed_width: 30;
        fixed_height: 30;
        frame_color: Theme.color("light1");
        highlight_color: Theme.color("red");
        frame_radius: 8;
        frame_enabled: true;
        icon_px_size: 18;
        icon_source: "qrc:/icons/trashbin.png";
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
