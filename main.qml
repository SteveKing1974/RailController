import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.elmsoft.qmlcomponents 1.0

ApplicationWindow {
    id: topLevel

    title: qsTr("Hello World")
    width: 1000
    height: 480
    visible: true

    property int baseLength: 200

    TrackSectionItem {
        width: 200
        height: 200
    }

//    property variant clickBoxes: [
//        [topLevel.width/2 - 10, topLevel.height/2 - 190],
//        [topLevel.width/2 - 10, topLevel.height/2+170],
//        [topLevel.width/2 - 10, topLevel.height/2-160],
//        [topLevel.width/2 - 10, topLevel.height/2+140],
//        [topLevel.width/2 - 10, topLevel.height/2+110],
//        [topLevel.width/2 - baseLength - 40, topLevel.height/2+110],
//        [topLevel.width/2 - 10, topLevel.height/2+80],

//        [topLevel.width/2 - baseLength - 70, topLevel.height/2+80],
//        [topLevel.width/2 - baseLength - 75, topLevel.height/2+50],
//        [topLevel.width/2 - baseLength - 80, topLevel.height/2+20],

//        [topLevel.width/2 + baseLength - 60, topLevel.height/2+80],

//        [topLevel.width/2 + baseLength + 20, topLevel.height/2+110],
//        [topLevel.width/2 + baseLength + 30, topLevel.height/2+80],
//        [topLevel.width/2 + baseLength + 40, topLevel.height/2+50],
//    ]


//    Controller {
//        id: controller
//    }


//    ServerPopup {
//        visible: !controller.connected
//        controllerObj: controller
//    }



//    TrackCanvas {
//        id: trackDisplay
//        lineModel: controller.lineModel
//    }

//    SelectControllerPopup
//    {
//        id: selectControllerDlg

//        lineModel: controller.lineModel

//        anchors.fill: parent

//        visible: false
//    }


//    // Refresh and send data
//    Column {
//        anchors.top: parent.top
//        anchors.left: parent.left
//        MouseArea {
//            width: 100
//            height: 50

//            Rectangle {
//                border.color: "black"
//                radius: 5
//                anchors.fill: parent

//                Text {
//                    text: "Refresh"
//                    anchors.centerIn: parent
//                }
//            }

//            onClicked: controller.refreshState()
//        }
//        MouseArea {
//            width: 100
//            height: 50

//            Rectangle {
//                border.color: "black"
//                color: parent.pressed ? "black" : "white"
//                radius: 5
//                anchors.fill: parent

//                Text {
//                    text: "Submit"
//                    anchors.centerIn: parent
//                }
//            }

//            onClicked: controller.refreshState()
//        }
//    }

//    // Click points
//    Repeater {
//        model: controller.lineModel
//        Rectangle {
//            x: clickBoxes[index][0]
//            y: clickBoxes[index][1]
//            width: 20
//            height: 20
//            color: controller.lineModel.controllerColour(controllerID)

//            radius: 10

//            MouseArea{
//                anchors.fill: parent
//                onClicked: selectControllerDlg.selectController(index, possibleControllers)
//            }
//        }
//    }

}
