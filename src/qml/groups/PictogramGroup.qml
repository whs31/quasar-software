import QtQuick 2.12
import "qrc:/qml/ui" as UI
import RuntimeData 1.0

Item {
    id: pictogramGroup;

    UI.ToolIcon {
        id: iconSatellites;
        tooltipenabled: true;
        tooltiptext: "Количество спутников навигации";
        iconsource: "qrc:/ui-resources/white/satellite.png";
        label: "<font color=\"#c7a750\">" + Number(RuntimeData.satellites) + "</font>";
    }
//    UI.ToolIcon {
//        id: iconLinkStatus;
//        anchors.top: iconSatellites.bottom;
//        anchors.topMargin: 30;
//        tooltipenabled: true;
//        tooltiptext: "Количество спутников навигации";
//        iconsource: "qrc:/ui-resources/white/link.png";
//        label: "<font color=\"#c7a750\">" + Number(RuntimeData.satellites) + "</font>";
//    }
}
