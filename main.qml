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

    LineStateModel {
        id: lineModel
    }

    property int baseLength: 200

    property variant clickBoxes: [
        [topLevel.width/2 - 10, topLevel.height/2 - 190],
        [topLevel.width/2 - 10, topLevel.height/2+170],
        [topLevel.width/2 - 10, topLevel.height/2-160],
        [topLevel.width/2 - 10, topLevel.height/2+140],
        [topLevel.width/2 - 10, topLevel.height/2+110],
        [topLevel.width/2 - baseLength - 40, topLevel.height/2+110],
        [topLevel.width/2 - 10, topLevel.height/2+80],

        [topLevel.width/2 - baseLength - 70, topLevel.height/2+80],
        [topLevel.width/2 - baseLength - 75, topLevel.height/2+50],
        [topLevel.width/2 - baseLength - 80, topLevel.height/2+20],

        [topLevel.width/2 + baseLength - 60, topLevel.height/2+80],
    ]


    Canvas {
        id: trackDisplay
        anchors.fill: parent

        onPaint: {
            // Get drawing context
            var context = getContext("2d");

            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);
            context.fill();


            // Outer line
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(0);
            context.arc(width/2 - baseLength, height/2, 180, Math.PI/2, -Math.PI/2, false)
            context.arc(width/2 + baseLength, height/2, 180, -Math.PI/2, Math.PI/2, false)
            context.stroke();

            context.beginPath()
            context.strokeStyle = lineModel.sectionColour(1)
            context.moveTo(width/2 + baseLength, height/2 + 180)
            context.lineTo(width/2 - baseLength, height/2 + 180)
            context.stroke();

            // Inner line
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(2)

            context.arc(width/2 - baseLength, height/2, 150, Math.PI/2, -Math.PI/2, false)
            context.arc(width/2 + baseLength, height/2, 150, -Math.PI/2, Math.PI/2, false)
            context.stroke();

            context.beginPath()
            context.strokeStyle = lineModel.sectionColour(3)
            context.moveTo(width/2 + baseLength, height/2 + 150)
            context.lineTo(width/2 - baseLength, height/2 + 150)

            context.stroke()

            // RH Outer points
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)

            context.moveTo(width/2 + baseLength - 30, height/2 + 150)
            context.lineTo(width/2 + baseLength, height/2 + 180)
            context.stroke()

            // LH Outer points
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)

            context.moveTo(width/2 - baseLength + 30, height/2 + 150)
            context.lineTo(width/2 - baseLength, height/2 + 180)
            context.stroke()

            // Station outer points
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)
            context.moveTo(width/2 + baseLength - 30, height/2 + 150)
            context.lineTo(width/2 + baseLength - 60, height/2 + 120)
            context.stroke()


            // Station outer
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(4)
            context.moveTo(width/2 + baseLength - 60, height/2 + 120)
            context.lineTo(width/2 - baseLength, height/2 + 120)
            context.stroke()

            // Run around
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(5)
            context.moveTo(width/2 - baseLength, height/2 + 120)
            context.lineTo(width/2 - baseLength - 60, height/2 + 120)
            context.stroke();


            // Station inner entry/exit points
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)
            context.moveTo(width/2 + baseLength - 60, height/2 + 120)
            context.lineTo(width/2 + baseLength - 90, height/2 + 90)
            context.stroke()
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)
            context.moveTo(width/2 - baseLength+30, height/2 + 90)
            context.lineTo(width/2 - baseLength, height/2 + 120)
            context.stroke()

            // Station inner
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(6)
            context.moveTo(width/2 + baseLength - 90, height/2 + 90)
            context.lineTo(width/2 - baseLength + 10, height/2 + 90)
            context.stroke();

            // LH Sidings entry points
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)
            context.moveTo(width/2 - baseLength + 10, height/2 + 90)
            context.lineTo(width/2 - baseLength - 50, height/2 + 30)
            context.stroke()

            // LH Sidings bottom
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(7)
            context.moveTo(width/2 - baseLength + 10, height/2 + 90)
            context.lineTo(width/2 - baseLength - 90, height/2 + 90)
            context.stroke()

            // LH Sidings middle
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(8)
            context.moveTo(width/2 - baseLength - 20, height/2 + 60)
            context.lineTo(width/2 - baseLength - 90, height/2 + 60)
            context.stroke()

            // LH Sidings top
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(9)
            context.moveTo(width/2 - baseLength - 50, height/2 + 30)
            context.lineTo(width/2 - baseLength - 90, height/2 + 30)
            context.stroke()

            // RH Station loading
            context.beginPath();
            context.strokeStyle = lineModel.sectionColour(10)
            context.moveTo(width/2 + baseLength - 90, height/2 + 90)
            context.lineTo(width/2 + baseLength - 30, height/2 + 90)
            context.stroke()

            // RH Sidings entry points
            context.beginPath();
            context.strokeStyle = lineModel.controllerColour(lineModel.eNoController)
            context.moveTo(width/2 + baseLength - 60, height/2 + 120)
            context.lineTo(width/2 + baseLength - 30, height/2 + 120)
            context.lineTo(width/2 + baseLength + 30, height/2 + 60)

//            context.moveTo(width/2 + baseLength - 90, height/2 + 120)
//            context.lineTo(width/2 + baseLength + 60, height/2 + 120)
//            context.moveTo(width/2 + baseLength - 30, height/2 + 120)
//            context.lineTo(width/2 + baseLength + 60, height/2 + 90)
//            context.moveTo(width/2 + baseLength - 30, height/2 + 120)
//            context.lineTo(width/2 + baseLength + 60, height/2 + 60)
            context.stroke()

        }
    }

    MouseArea {
        id: selectControllerDlg

        anchors.fill: parent

        onClicked: selectControllerDlg.visible = false

        visible: false

        z: 2

        Rectangle {
            color: "black"
            opacity: 0.5
            anchors.fill: parent
        }

        onVisibleChanged: {
            if (!visible)
            {
                popupContent.modelIndex = -1
                popupContent.v = []
            }
        }

        function selectController(sectionIndex, possibleControllers)
        {
            popupContent.modelIndex = sectionIndex
            popupContent.v = possibleControllers
            visible = true
        }

        function refreshDisplay()
        {
            trackDisplay.requestPaint()
        }


        Rectangle {
            id: popupRect

            anchors.centerIn: parent

            color: "white"
            width: 200
            height: 200

            border.color: "black"
            border.width: 4
            radius: 10

            ListView {
                id: popupContent

                anchors.fill: parent
                anchors.margins: 30

                property variant v: []
                property int modelIndex: -1

                model: v
                delegate: Text {
                    text: lineModel.controllerName(popupContent.v[index])
                    height: 30
                    color: "black"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            lineModel.changeController(popupContent.modelIndex, popupContent.v[index])
                            selectControllerDlg.refreshDisplay()
                            selectControllerDlg.visible = false
                        }
                    }
                }
            }
        }
    }

    // Click points
    Repeater {
        model: lineModel
        Rectangle {
            x: clickBoxes[index][0]
            y: clickBoxes[index][1]
            width: 20
            height: 20
            color: lineModel.controllerColour(controllerID)

            MouseArea{
                anchors.fill: parent
                onClicked: selectControllerDlg.selectController(index, possibleControllers)
            }
        }
    }

}
