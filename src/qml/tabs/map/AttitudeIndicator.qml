import QtQuick 2.15
import QtQuick3D 1.15

Rectangle {
    radius: 10;

    property bool shown: false;
    property real pitch;
    property real roll;
    property real yaw;

    height: shown ? implicitHeight : 0;
    visible: height > 0;
    Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 200; } }
    clip: true;

    Rectangle { color: parent.color; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 10; }

    View3D {
        anchors.fill: parent;
        anchors.topMargin: 5;
        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.Transparent;
            antialiasingMode: SceneEnvironment.SSAA;
        }

        PerspectiveCamera {
            position: Qt.vector3d(0, 0, 110);
        }

        DirectionalLight  {
            position: Qt.vector3d(0, 0, 0);
        }

        Model {
            position: Qt.vector3d(0, 0, 0);
            source: "#Sphere";
            eulerRotation.x: -pitch;
            eulerRotation.y: yaw;
            eulerRotation.z: roll;
            materials: [
                DefaultMaterial  {
                    diffuseMap: Texture {
                        source: "qrc:/textures/attitude.png";
                        scaleU: 1.0;
                        scaleV: 1.0;
                    }
                }
            ]
        }
    }
}
