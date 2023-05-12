import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Telemetry 1.0
import Execd 1.0

Pane {
    Material.elevation: 20;
    opacity: 0.5;

    CheckBox { id: checkbox_Telsrv;
        text: "Сервер телеметрии";
        onCheckedChanged: {
            if(checked)
                TelemetrySocket.startTelemetryServer();
            else
                TelemetrySocket.stop();
        }
    }

    CheckBox { id: checkbox_Execdsrv;
        text: "Сервер команд";
        anchors.top: checkbox_Telsrv.bottom;
    }

    CheckBox { id: checkbox_Feedbacksrv;
        text: "Сервер фидбэка";
        anchors.top: checkbox_Execdsrv.bottom;

        onCheckedChanged: {
            if(checked)
                Feedback.setAddress("127.0.0.1:9846");
            else
                Feedback.setAddress("");
        }
    }

    CheckBox { id: checkbox_Fsend;
        text: "Клиент TCP-IP";
        anchors.top: checkbox_Feedbacksrv.bottom;

    }

    Button { id: btn_SendTestFeedback;
        anchors.top: checkbox_Fsend.bottom;
        anchors.topMargin: 5;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "Тест фидбэка";

        onPressed: Feedback.testVT100();
    }
}
