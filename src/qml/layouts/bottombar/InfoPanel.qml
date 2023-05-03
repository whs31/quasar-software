import QtQuick 2.15
import Theme 1.0
import Network 1.0
import Widgets.Status 1.0

Item {
    property real fl_Latitude: Network.telemetry.latitude;
    property real fl_Longitude: Network.telemetry.longitude;
    property real fl_Altitude: Network.telemetry.altitude;
    property real fl_SeaAltitude: Network.telemetry.altitude;
    property real fl_Velocity: Network.telemetry.velocityCourse;
    property real fl_Direction: Network.telemetry.course;
    property int i_SatellitesCount: Network.telemetry.satellites;
    property real fl_ConnectionDelay: Network.networkDelay;
    property real fl_RemoteDiskSpace: Network.remoteData.storageSpace;

    width: 915;
    height: 46;

    Image { id: ico_LatIcon;
        width: 16;
        height: 16;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/latitude.png";
    }

    Text { id: txt_Lat;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ШИРОТА:";
        width: 75;
        height: 12;
        anchors.top: ico_LatIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_LatIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_LatValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_Latitude).toFixed(7) + "° N";
        width: 100;
        height: 12;
        anchors.top: txt_Lat.top;
        anchors.left: txt_Lat.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Image { id: ico_LonIcon;
        width: 16;
        height: 16;
        anchors.left: parent.left;
        anchors.top: ico_LatIcon.bottom;
        anchors.topMargin: 2;
        source: "qrc:/icons/bottombar/longitude.png";
    }

    Text { id: txt_Lon;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ДОЛГОТА:";
        width: 75;
        height: 12;
        anchors.top: ico_LonIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_LonIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_LonValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_Longitude).toFixed(7) + "° E";
        width: 100;
        height: 12;
        anchors.top: txt_Lon.top;
        anchors.left: txt_Lon.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Rectangle { id: rect_Separator1;
        width: 2;
        height: 32;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: txt_LatValue.right;
        color: Theme.color("dark3");
    }

    Image { id: ico_AltIcon;
        width: 16;
        height: 16;
        anchors.left: rect_Separator1.right;
        anchors.leftMargin: 8;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/altitude.png";
    }

    Text { id: txt_Alt;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ВЫСОТА:";
        width: 140;
        height: 12;
        anchors.top: ico_AltIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_AltIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_AltValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 16;
        text: Number(fl_Altitude).toFixed(0) + " м";
        width: 56;
        height: 16;
        anchors.top: txt_Alt.top;
        anchors.topMargin: -4;
        anchors.left: txt_Alt.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Image { id: ico_SeaIcon;
        width: 16;
        height: 16;
        anchors.left: ico_AltIcon.left;
        anchors.top: ico_AltIcon.bottom;
        anchors.topMargin: 2;
        source: "qrc:/icons/bottombar/sea-level.png";
    }

    Text { id: txt_Sea;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "НАД УРОВНЕМ МОРЯ:";
        width: 140;
        height: 12;
        anchors.top: ico_SeaIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_SeaIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_SeaValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_SeaAltitude).toFixed(0) + " м";
        width: 56;
        height: 12;
        anchors.top: txt_Sea.top;
        anchors.left: txt_Sea.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Rectangle { id: rect_Separator2;
        width: 2;
        height: 32;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: txt_SeaValue.right;
        color: Theme.color("dark3");
    }

    Image { id: ico_SpeedIcon;
        width: 16;
        height: 16;
        anchors.left: rect_Separator2.right;
        anchors.leftMargin: 8;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/speed.png";
    }

    Text { id: txt_Speed;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "СКОРОСТЬ:";
        width: 82;
        height: 12;
        anchors.top: ico_SpeedIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_SpeedIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_SpeedValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 16;
        text: Number(fl_Velocity).toFixed(0) + " км/ч";
        width: 74;
        height: 16;
        anchors.top: txt_Speed.top;
        anchors.topMargin: -4;
        anchors.left: txt_Speed.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Image { id: ico_DirectionIcon;
        width: 16;
        height: 16;
        anchors.left: ico_SpeedIcon.left;
        anchors.top: ico_SpeedIcon.bottom;
        anchors.topMargin: 2;
        source: "qrc:/icons/bottombar/compass.png";
    }

    Text { id: txt_Direction;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "АЗИМУТ:";
        width: 82;
        height: 12;
        anchors.top: ico_DirectionIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_DirectionIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Text { id: txt_DirectionValue;
        color: Theme.color("light0");
        font.weight: Font.DemiBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_Direction).toFixed(1) + "°";
        width: 74;
        height: 12;
        anchors.top: txt_Direction.top;
        anchors.left: txt_Direction.right;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Rectangle { id: rect_Separator3;
        width: 2;
        height: 32;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: txt_DirectionValue.right;
        color: Theme.color("dark3");
    }

    Image { id: ico_Satellites;
        width: 16;
        height: 16;
        anchors.left: rect_Separator3.right;
        anchors.leftMargin: 8;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/satellite.png";
    }

    Text { id: txt_Satellites;
        property string s_CurrentColor: i_SatellitesCount < 3 ? "red" : i_SatellitesCount < 6 ? "yellow" : "green";
        color: Theme.color("light0");
        font.weight: Font.Bold;
        font.family: root.s_FontMain;
        font.pixelSize: 13;
        text: Theme.colorText(Number(i_SatellitesCount).toFixed(0), s_CurrentColor) + " спутников";
        width: 110;
        height: 12;
        anchors.top: ico_Satellites.top;
        anchors.topMargin: 2;
        anchors.left: ico_Satellites.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Image { id: ico_DelayIcon;
        width: 16;
        height: 16;
        anchors.left: ico_Satellites.left;
        anchors.top: ico_Satellites.bottom;
        anchors.topMargin: 2;
        source: "qrc:/icons/bottombar/ping.png";
    }

    Text { id: txt_Delay;
        property string s_CurrentColor: fl_ConnectionDelay < 3 ? "green" : fl_ConnectionDelay < 8 ? "yellow" : "red";
        color: Theme.color("light0");
        font.weight: Font.Bold;
        font.family: root.s_FontMain;
        font.pixelSize: 13;
        text: "Задержка " + Theme.colorText( + Number(fl_ConnectionDelay).toFixed(1) + " с", s_CurrentColor);
        width: 110;
        height: 12;
        anchors.top: ico_DelayIcon.top;
        anchors.topMargin: 2;
        anchors.left: ico_DelayIcon.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    Rectangle { id: rect_Separator4;
        width: 2;
        height: 32;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: txt_Delay.right;
        color: Theme.color("dark3");
    }

    Image { id: ico_Disk;
        width: 16;
        height: 16;
        anchors.left: rect_Separator4.right;
        anchors.leftMargin: 8;
        anchors.top: parent.top;
        anchors.topMargin: 6;
        source: "qrc:/icons/bottombar/disc.png";
    }

    Text { id: txt_Disk;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: "ХРАНИЛИЩЕ НА РЛС";
        width: 82;
        height: 12;
        anchors.top: ico_Disk.top;
        anchors.topMargin: 2;
        anchors.left: ico_Disk.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    ProgressBar { id: c_DiskProgressBar;
        width: 107;
        height: 10;
        anchors.left: ico_Disk.left;
        anchors.top: ico_Disk.bottom;
        anchors.topMargin: 7;
        value: fl_RemoteDiskSpace * 100;
        errorColor: Theme.color("red");
        warnColor: Theme.color("yellow");
        successColor: Theme.color("green");
        backgroundColor: Theme.color("light0");
    }

    Text { id: txt_DiskValue;
        color: Theme.color("light0");
        font.weight: Font.ExtraBold;
        font.family: root.s_FontMain;
        font.pixelSize: 12;
        text: Number(fl_RemoteDiskSpace * 100).toFixed(0) + "%";
        width: 40;
        height: 12;
        anchors.top: c_DiskProgressBar.top;
        anchors.topMargin: -1;
        anchors.left: c_DiskProgressBar.right;
        anchors.leftMargin: 5;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }
}
