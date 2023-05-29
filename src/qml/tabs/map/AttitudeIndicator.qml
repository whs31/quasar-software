import QtQuick 2.15
import QtQuick3D 1.15
import Theme 1.0

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

    View3D { id: view3d;
        anchors.fill: parent;
        anchors.topMargin: 5;
        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.Transparent;
            antialiasingMode: SceneEnvironment.SSAA;
        }

        OrthographicCamera {
            position: Qt.vector3d(0, 0, 500);
        }

        DirectionalLight  {
            position: Qt.vector3d(0, 0, 0);
            shadowFactor: 1;
            brightness: 135;
        }

        Model {
            position: Qt.vector3d(0, 0, 0);
            scale: Qt.vector3d(3, 3, 3);
            source: "#Sphere";
            eulerRotation.x: -pitch;
            eulerRotation.y: yaw;
            eulerRotation.z: roll;
            Behavior on eulerRotation.x { NumberAnimation { duration: 100; } }
            Behavior on eulerRotation.y { NumberAnimation { duration: 100; } }
            Behavior on eulerRotation.z { NumberAnimation { duration: 100; } }
            materials: [
                DefaultMaterial  {
                    diffuseMap: Texture {
                        source: "qrc:/textures/attitude-alt.png";
                        scaleU: 1.0;
                        scaleV: 1.0;
                    }
                }
            ]
        }
    }

    Rectangle { anchors.centerIn: view3d; color: Theme.color("color2"); height: 5; width: 5; radius: 2.5; }
}
