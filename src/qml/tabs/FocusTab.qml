import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15

import Theme 1.0
import Images 1.0
import Network 1.0

import "focus" as FocusTab

Rectangle { id: focustab_root;
    color: ColorTheme.active.color(ColorTheme.Dark)

    property int currentAssignedIndex: -1;
    property int currentTool: 0; // 0 - hand, 1 - focus

    property real currentStep: 0;
    property real currentLx: 0;
    property real currentLy: 0;
    property real currentX0: 0;

    onCurrentAssignedIndexChanged: {
        if(currentAssignedIndex >= 0) {
            mapImage.source = "file:" + ImagesModel.getRole(currentAssignedIndex, "filepath");
            currentStep = ImagesModel.getRole(currentAssignedIndex, "dx");
            currentLx = ImagesModel.getRole(currentAssignedIndex, "lx");
            currentLy = ImagesModel.getRole(currentAssignedIndex, "ly");
            currentX0 = ImagesModel.getRole(currentAssignedIndex, "x0");
            filename_label.filename_string = ImagesModel.getRole(currentAssignedIndex, "filename")

            panel_Reform.setVelocityAndElevation(Number(ImagesModel.getRole(currentAssignedIndex, "velocity")).toFixed(1),
                                                 Number(ImagesModel.getRole(currentAssignedIndex, "elevation")).toFixed(1));

            Network.setArgument("-f", ImagesModel.getRole(currentAssignedIndex, "filename"), Net.Reform);
            Network.setArgument("-f", ImagesModel.getRole(currentAssignedIndex, "filename"), Net.Focus);
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
            color: ColorTheme.active.color(ColorTheme.Dark)
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
                anchors.centerIn: parent;
                fillMode: Image.PreserveAspectFit;

                MouseArea { id: mouseAreaImage;
                    enabled: currentTool === 1;
                    anchors.fill: parent;
                    propagateComposedEvents: true;
                }

                Rectangle {
                    property bool shown: currentTool === 1;
                    border.color: ColorTheme.active.color(ColorTheme.Orange)
                    border.width: 2;
                    color: "transparent";
                    width: panel_FocusSettings.focus_ls * currentStep;
                    height: width;
                    opacity: shown ? 0.9 : 0;
                    Behavior on opacity { NumberAnimation { duration: 300; } }
                    enabled: shown;
                    x: mouseAreaImage.mouseX - width / 2;
                    y: mouseAreaImage.mouseY - height / 2;
                    onXChanged: panel_FocusSettings.focus_px = (x / mapImage.width) * currentLx * currentStep + currentX0;
                    onYChanged: panel_FocusSettings.focus_py = ((y / mapImage.height) - 0.5) * currentLy * currentStep;

                    Image { id: pattern;
                        source: "qrc:/map/patterns/diagonal.png";
                        anchors.fill: parent;
                        visible: false;
                    }

                    ColorOverlay {
                        anchors.fill: pattern;
                        source: pattern;
                        color: ColorTheme.active.color(ColorTheme.Orange)
                        smooth: true;
                        antialiasing: true;
                    }
                }
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

                    MouseArea { id: testMouseArea;
                        anchors.fill: parent
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
            color: ColorTheme.active.color(ColorTheme.Text)
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

    FocusTab.PanelEditorToolbar { id: panel_EditorToolbar;
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 5
        }
    }

    FocusTab.PanelToolbar { id: panel_Toolbar;
        opacity: 0.85;
        anchors {
            right: parent.right
            top: parent.top
            margins: 5
        }
    }

    FocusTab.FocusSettings { id: panel_FocusSettings;
        property bool shown: currentTool === 1;

        opacity: shown ? 0.9 : 0;
        Behavior on opacity { NumberAnimation { duration: 300; } }
        enabled: shown;
        anchors {
            horizontalCenter: flick.horizontalCenter
            bottom: panel_EditorToolbar.top
            bottomMargin: 15
        }
    }
}
