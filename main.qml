import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 1000
    height: 480
    visible: true

    Canvas {
        anchors.fill: parent

        onPaint: {
            // Get drawing context
            var context = getContext("2d");

            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);
            context.fill();

            var baseLength = 200

            // Outer line
            context.beginPath();
            context.strokeStyle = "red"
            context.arc(width/2 - baseLength, height/2, 180, Math.PI/2, -Math.PI/2, false)
            context.arc(width/2 + baseLength, height/2, 180, -Math.PI/2, Math.PI/2, false)
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
