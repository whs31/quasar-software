import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import Theme 1.0
import Images 1.0
import Network 1.0

import "focus" as FocusTab

Rectangle { id: focustab_root;
    color: Theme.color("dark0");

    property int currentAssignedIndex: -1;
    onCurrentAssignedIndexChanged: {
        if(currentAssignedIndex >= 0) {
            mapImage.source = "file:///" + ImagesModel.getRole(currentAssignedIndex, "filepath");
            filename_label.filename_string = Theme.colorText(ImagesModel.getRole(currentAssignedIndex, "filename"), Theme.color("yellow"));

            panel_Reform.setVelocityAndElevation(Number(ImagesModel.getRole(currentAssignedIndex, "velocity")).toFixed(1),
                                                 Number(ImagesModel.getRole(currentAssignedIndex, "elevation")).toFixed(1));

            Network.setArgument("-f", ImagesModel.getRole(currentAssignedIndex, "filename"), Network.Reform);
            Network.setArgument("-f", ImagesModel.getRole(currentAssignedIndex, "filename"), Network.Focus);
        }
    }

    Connections {
        target: ImagesModel;
        function onTotalCountChanged()
        {
            currentAssignedIndex = -1;
        }
    }

    Flickable { id: flick;
        anchors {
            left: panel_Param.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        clip: true;
        boundsBehavior: Flickable.StopAtBounds;

        Rectangle {
            id: rect;
            color: Theme.color("dark0");
            width: Math.max(mapImage.sourceSize.width, flick.width);
            height: Math.max(mapImage.sourceSize.height, flick.height);
            transform: Scale {
                id: scaler;
                origin.x: pinchArea.m_x2;
                origin.y: pinchArea.m_y2;
                xScale: pinchArea.m_zoom2;
                yScale: pinchArea.m_zoom2;
            }

            Image { id: mapImage;
                z: dragArea.z + 1;
                source: "qrc:/map/patterns/diagonal.png";
                anchors.centerIn: parent;
                fillMode: Image.PreserveAspectFit;
            }

            PinchArea { id: pinchArea;
                anchors.fill: parent;
                property real m_x1: 0;
                property real m_y1: 0;
                property real m_y2: 0;
                property real m_x2: 0;
                property real m_zoom1: 1;
                property real m_zoom2: 1;
                property real m_max: 3;
                property real m_min: 0.5;

                onPinchStarted: {
                    m_x1 = scaler.origin.x;
                    m_y1 = scaler.origin.y;
                    m_x2 = pinch.startCenter.x;
                    m_y2 = pinch.startCenter.y;
                    rect.x = rect.x + (pinchArea.m_x1 - pinchArea.m_x2) * (1 - pinchArea.m_zoom1);
                    rect.y = rect.y + (pinchArea.m_y1 - pinchArea.m_y2) * (1 - pinchArea.m_zoom1);
                }
                onPinchUpdated: {
                    m_zoom1 = scaler.xScale;
                    var dz = pinch.scale - pinch.previousScale;
                    var newZoom = m_zoom1 + dz;
                    if(newZoom <= m_max && newZoom >= m_min)
                        m_zoom2 = newZoom;
                }
                MouseArea { id: dragArea;
                    hoverEnabled: true;
                    anchors.fill: parent;
                    drag.target: rect;
                    drag.filterChildren: true;

                    onWheel: {
                        pinchArea.m_x1 = scaler.origin.x;
                        pinchArea.m_y1 = scaler.origin.y;
                        pinchArea.m_zoom1 = scaler.xScale;
                        pinchArea.m_x2 = mouseX;
                        pinchArea.m_y2 = mouseY;

                        var newZoom;
                        if(wheel.angleDelta.y > 0)
                        {
                            newZoom = pinchArea.m_zoom1 + 0.1;
                            if(newZoom <= pinchArea.m_max)
                                pinchArea.m_zoom2 = newZoom;
                            else
                                pinchArea.m_zoom2 = pinchArea.m_max;
                        }
                        else
                        {
                            newZoom = pinchArea.m_zoom1-0.1
                            if(newZoom >= pinchArea.m_min)
                                pinchArea.m_zoom2 = newZoom
                            else
                                pinchArea.m_zoom2 = pinchArea.m_min
                        }
                        rect.x = rect.x + (pinchArea.m_x1 - pinchArea.m_x2) * (1 - pinchArea.m_zoom1);
                        rect.y = rect.y + (pinchArea.m_y1 - pinchArea.m_y2) * (1 - pinchArea.m_zoom1);
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: console.log("Click in child")
                    }
                }
            }
        }
    }

    Pane {
        anchors {
            top: flick.top
            topMargin: 30
            horizontalCenter: flick.horizontalCenter
        }

        Material.elevation: 100;

        Text { id: filename_label;
            property string filename_string: "null";

            text: "Редактирование файла " + "<b>" + filename_string + "</b>";
            font {
                family: root.mainfont
                pixelSize: 15
            }
            color: Theme.color("light1");
        }
    }

    Pane { id: panel_Param;
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            margins: 10
        }
        width: 500;

        Column {
            anchors.fill: parent;

            FocusTab.ReformSettings { id: panel_Reform; }
        }
    }
}
/*

            {"--px", ExecdArgument(-1.0f)},         //! @var Координата по дальности точки для фокусировки
            {"--py", ExecdArgument(-1.0f)},         //! @var Координата по путевой дальности точки для фокусировки.
            {"--ls", ExecdArgument(50.0f)},         //! @var Размер стороны квадрата в м, по которой производится фокусировка
            {"--vmin", ExecdArgument(-1.0f)},       //! @var Минимальное  значение гипотезы по скорости для фокусировки, км/ч
            {"--vmax", ExecdArgument(-1.0f)},       //! @var Максимальное значение гипотезы по скорости для фокусировки, км/ч
            {"--ni", ExecdArgument(10)},            //! @var Количество гипотез по скорости [1 - inf]
            */
