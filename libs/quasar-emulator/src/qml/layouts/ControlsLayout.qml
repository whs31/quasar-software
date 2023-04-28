import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Pane {
    Material.elevation: 20;
    opacity: 0.5;

    CheckBox { id: checkbox_Telsrv;
        text: "Сервер телеметрии";
    }

    CheckBox { id: checkbox_Execdsrv;
        text: "Сервер команд";
        anchors.top: checkbox_Telsrv.bottom;
        anchors.topMargin: 1;
    }

    CheckBox { id: checkbox_Feedbacksrv;
        text: "Сервер фидбэка";
        anchors.top: checkbox_Execdsrv.bottom;
        anchors.topMargin: 1;
    }

    CheckBox { id: checkbox_Fsend;
        text: "Клиент TCP-IP";
        anchors.top: checkbox_Feedbacksrv.bottom;
        anchors.topMargin: 1;
    }

    Button { id: btn_SendTestFeedback;
        anchors.top: checkbox_Fsend.bottom;
        anchors.topMargin: 5;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "Тест фидбэка";
    }
}
