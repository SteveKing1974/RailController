import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: topLevel

    title: qsTr("Hello World")
    width: 1000
    height: 480
    visible: true

    property int baseLength: 200

    property variant controllerNames: ["Off", "Controller 1", "Controller 2", "Controller 3"]
    property variant controllerColours: ["black", "red", "blue", "green"]
    property variant outerTop: [0, [0, 1]]



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
            context.strokeStyle = controllerColours[outerTop[0]]
            context.arc(width/2 - baseLength, height/2, 180, Math.PI/2, -Math.PI/2, false)
            context.arc(width/2 + baseLength, height/2, 180, -Math.PI/2, Math.PI/2, false)
            context.stroke();

            context.beginPath()
            context.strokeStyle = "red"
            context.moveTo(width/2 + baseLength, height/2 + 180)
            context.lineTo(width/2 - baseLength, height/2 + 180)
            context.stroke();

            // Inner line
            context.beginPath();
            context.strokeStyle = "blue"

            context.arc(width/2 - baseLength, height/2, 150, Math.PI/2, -Math.PI/2, false)
            context.arc(width/2 + baseLength, height/2, 150, -Math.PI/2, Math.PI/2, false)
            context.lineTo(width/2 - baseLength, height/2 + 150)

            context.stroke()

            // RH Outer points
            context.beginPath();
            context.strokeStyle = "red"

            context.moveTo(width/2 + baseLength - 30, height/2 + 150)
            context.lineTo(width/2 + baseLength, height/2 + 180)
            context.stroke()

            // LH Outer points
            context.beginPath();
            context.strokeStyle = "red"

            context.moveTo(width/2 - baseLength + 30, height/2 + 150)
            context.lineTo(width/2 - baseLength, height/2 + 180)
            context.stroke()

            // Station outer
            context.beginPath();
            context.strokeStyle = "green"

            context.moveTo(width/2 + baseLength - 30, height/2 + 150)
            context.lineTo(width/2 + baseLength - 60, height/2 + 120)
            context.lineTo(width/2 - baseLength - 60, height/2 + 120)
            context.stroke()

            // Station inner
            context.beginPath();
            context.strokeStyle = "green"

            context.moveTo(width/2 + baseLength - 60, height/2 + 120)
            context.lineTo(width/2 + baseLength - 90, height/2 + 90)
            context.lineTo(width/2 - baseLength+30, height/2 + 90)
            context.lineTo(width/2 - baseLength, height/2 + 120)
            context.stroke()

            // LH Sidings
            context.beginPath();
            context.strokeStyle = "green"

            context.moveTo(width/2 - baseLength+30, height/2 + 90)
            context.lineTo(width/2 - baseLength - 90, height/2 + 90)
            context.moveTo(width/2 - baseLength, height/2 + 90)
            context.lineTo(width/2 - baseLength - 90, height/2 + 60)
            context.moveTo(width/2 - baseLength, height/2 + 90)
            context.lineTo(width/2 - baseLength - 90, height/2 + 30)
            context.stroke()

            // RH Sidings
            context.beginPath();
            context.strokeStyle = "green"

            context.moveTo(width/2 + baseLength - 90, height/2 + 90)
            context.lineTo(width/2 + baseLength - 60, height/2 + 90)
            context.moveTo(width/2 + baseLength - 90, height/2 + 120)
            context.lineTo(width/2 + baseLength + 60, height/2 + 120)
            context.moveTo(width/2 + baseLength - 30, height/2 + 120)
            context.lineTo(width/2 + baseLength + 60, height/2 + 90)
            context.moveTo(width/2 + baseLength - 30, height/2 + 120)
            context.lineTo(width/2 + baseLength + 60, height/2 + 60)
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
                popupContent.v = []
            }
        }

        function selectController(controllerVar)
        {
            popupContent.v = controllerVar
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

                model: v.length==2 ? v[1].length : null
                delegate: Text {
                    text: controllerNames[popupContent.v[1][index]]
                    height: 30
                    color: "black"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            popupContent.v[0] = index
                            selectControllerDlg.refreshDisplay()
                            selectControllerDlg.visible = false
                        }
                    }
                }
            }
        }
    }

    // Click points
    Rectangle {
        x: parent.width/2 - 10
        y: parent.height/2 - 190
        width: 20
        height: 20
        color: controllerColours[outerTop[0]]

        MouseArea{
            anchors.fill: parent
            onClicked: selectControllerDlg.selectController(outerTop)
        }
    }



//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("&File")
//            MenuItem {
//                text: qsTr("&Open")
//                onTriggered: messageDialog.show(qsTr("Open action triggered"));
//            }
//            MenuItem {
//                text: qsTr("E&xit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

//    MainForm {
//        anchors.fill: parent
//        button1.onClicked: messageDialog.show(qsTr("Button 1 pressed"))
//        button2.onClicked: messageDialog.show(qsTr("Button 2 pressed"))
//        button3.onClicked: messageDialog.show(qsTr("Button 3 pressed"))
//    }

//    MessageDialog {
//        id: messageDialog
//        title: qsTr("May I have your attention, please?")

//        function show(caption) {
//            messageDialog.text = caption;
//            messageDialog.open();
//        }
//    }
}
