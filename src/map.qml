import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtLocation 5.0
import QtPositioning 5.0

//import cpp.invoker 1.0


Rectangle {
    /*Invoker {
        id: invoker
    }*/
    property double latitude: 0.0
    property double longitude: 0.0
    property double elevation: 0.0
    property double velocity: 0.0
    property var panToCurrentlocation: QtPositioning.coordinate(51.660784, 39.200268);

    function getTelemetry(lat, lon, elv, speed)
    {
        latitude = lat; longitude = lon; elevation = elv; velocity = speed;
        latText.text = qsTr(lat.toFixed(5).toString());
        lonText.text = qsTr(lon.toFixed(5).toString());
        spdText.text = qsTr(elv.toFixed(5).toString());
        elvText.text = qsTr(speed.toFixed(5).toString());
        panGPS();
        drawRoute(lat, lon);
    }

    function getMessage(msg)
    {
        msgText.text = qsTr(msg);
    }

    function panGPS()
    {
        mapView.center = panToCurrentlocation;
        panToCurrentlocation = QtPositioning.coordinate(latitude,longitude);
    }

    function drawRoute(lat, lon)
    {
        mapPolyline.addCoordinate(QtPositioning.coordinate(lat,lon));
    }

    id:main
    color: "#282828"
    radius: 9
    border.width: 3
    border.color: "#606060"

    Item {
        id: element
        anchors.fill: parent

        GroupBox {
            id: groupBox
            width: 206
            height: 119
            wheelEnabled: false
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            font.capitalization: Font.AllUppercase
            enabled: true
            font.weight: Font.Normal
            font.bold: true
            font.family: "Verdana"
            title: qsTr("<font color='white'><b>Телеметрия</b></font>")

            Text {
                id: element1
                color: "#ffffff"
                text: qsTr("Широта:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: element2
                color: "#ffffff"
                text: qsTr("Долгота:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 20
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: element3
                color: "#ffffff"
                text: qsTr("Высота: ")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 40
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: element4
                color: "#ffffff"
                text: qsTr("Скорость:")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 60
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: latText
                color: "#e2c700"
                text: qsTr("0.0000")
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 88
                anchors.top: parent.top
                anchors.topMargin: 0
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: lonText
                color: "#e2c700"
                text: qsTr("0.0000")
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 88
                anchors.top: parent.top
                anchors.topMargin: 21
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: elvText
                color: "#e2c700"
                text: qsTr("0.0000")
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 88
                anchors.top: parent.top
                anchors.topMargin: 41
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: spdText
                color: "#e2c700"
                text: qsTr("0.0000")
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: 88
                anchors.top: parent.top
                anchors.topMargin: 60
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }

        }

        GroupBox {
            id: groupBox1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.left: groupBox.right
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            font.capitalization: Font.AllUppercase
            enabled: true
            font.weight: Font.Normal
            font.bold: true
            font.family: "Verdana"
            title: qsTr("<font color='white'><b>Карта</b></font>")

            Map {
                id: mapView
                visible: true
                anchors.rightMargin: 5
                anchors.leftMargin: 5
                anchors.bottomMargin: 5
                anchors.topMargin: 5
                anchors.fill: parent
                plugin: Plugin {
                    id: mapPluginID;
                    name: "osm";
                    PluginParameter {
                        name: "osm.mapping.providersrepository.address";
                        value: "file://home/user/quasar-ui/QuaSAR-UI/osmconfigs";
                    }
                }
                activeMapType: mapView.supportedMapTypes[6]
                center: QtPositioning.coordinate(59.660784, 30.200268);
                zoomLevel: 15
                copyrightsVisible: false
                MapPolyline {
                    id: mapPolyline
                    line.width: 4
                    opacity: 0.8
                    line.color: '#e2c700'
                    path: [ ]
                }
                //Behavior on center {
                //    CoordinateAnimation {
                //        duration: 1000
                 //       easing.type: Easing.Linear
                  //  }
                //}
            }
        }
        GroupBox {
            id: groupBox2
            width: 206
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            wheelEnabled: false
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: groupBox.bottom
            anchors.topMargin: 8
            font.capitalization: Font.AllUppercase
            enabled: true
            font.weight: Font.Normal
            font.bold: true
            font.family: "Verdana"
            title: qsTr("<font color='white'><b>Диалоговое окно</b></font>")

            Text {
                id: element5
                color: "#ffffff"
                text: qsTr("Сообщение от РЛС: ")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 0
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }
            Text {
                id: msgText
                color: "#928a4a"
                text: qsTr("-------------")
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.FixedSize
                style: Text.Sunken
                font.italic: false
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                font.bold: true
                anchors.top: parent.top
                anchors.topMargin: 30
                font.family: "Verdana"
                textFormat: Text.RichText
                font.pixelSize: 12
            }

            Button {
                id: buttonFormImage
                text: qsTr("Формирование РЛИ")
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                highlighted: true
                flat: true
                font.pointSize: 7
                font.family: "Verdana"
                anchors.bottom: parent.bottomesri
                anchors.bottomMargin: 5
                //onClicked: invoker.formImageButton();
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:11;anchors_height:200}D{i:16;anchors_height:119}
D{i:2;anchors_width:206}
}
##^##*/
