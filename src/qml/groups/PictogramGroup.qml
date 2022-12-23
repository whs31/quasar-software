import QtQuick 2.12
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Item {
    id: pictogramGroup;

    UI.ToolIcon {
        id: iconLinkStatus;
        tooltipenabled: true;
        tooltiptext: "Статус подключения к РЛС: " + (!RuntimeData.connected ? "<b><font color=\"#b16573\">нет соединения</font></b>" : "<b><font color=\"#73c924\">соединение установлено</font></b>");
        iconsource: "qrc:/ui-resources/white/link.png";
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        basewidth: 30;
        primarycolor: RuntimeData.connected ? "#73c924" : "#b16573";
    }

    UI.ToolIcon {
        id: iconLinkInfo;
        tooltipenabled: true;
        anchors.top: iconLinkStatus.bottom;
        anchors.topMargin: 30;
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        basewidth: 30;
        tooltiptext: "IP-адрес РЛС: <font color=\"#43a1ca\"><b>" + RuntimeData.sarIP + "</b></font><br> 
                        IP-адрес АРМ: <font color=\"#43a1ca\"><b>" + RuntimeData.pcIP + "</b></font><br> 
                        Порт телеметрии: <font color=\"#bc9117\"><b>" + RuntimeData.telemetryPort + "</b></font>, 
                        порт загрузчика: <font color=\"#bc9117\"><b>" + RuntimeData.loaderPort + "</b></font>,<br> 
                        порт интерфейса формирования: <font color=\"#c7a750\"><b>" + RuntimeData.commandPort + "</b></font>, 
                        порт обратной связи <font color=\"#c7a750\"><b>" + RuntimeData.listenPort + "</b></font>";
        iconsource: "qrc:/ui-resources/white/connection-info.png";
        label: "";
    }

    UI.ToolIcon {
        id: iconSatellites;
        tooltipenabled: true;
        anchors.top: iconLinkInfo.bottom;
        anchors.topMargin: 30;
        tooltiptext: "Количество спутников навигации";
        iconsource: "qrc:/ui-resources/white/satellite.png";
        label: "<font color=\"#c7a750\">" + Number(RuntimeData.satellites) + "</font>";
    }
}
