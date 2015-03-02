import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    Canvas {
        width: 400
        height: 400

        onPaint: {
            // Get drawing context
            var context = getContext("2d");

            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);
            context.fill();

            // Fill inside with blue, leaving 10 pixel border
            context.beginPath();
            context.fillStyle = "blue"
            context.fillRect(10, 10, width - 20, height - 20);
            context.fill();

            // Draw a line
            context.beginPath();
            context.lineWidth = 2;
            context.moveTo(30, 30);
            context.strokeStyle = "red"
            context.lineTo(width-30, height-30);
            context.stroke();

            // Draw a circle
            context.beginPath();
            context.fillStyle = "orange"
            context.strokeStyle = "red"
            context.moveTo(width/2+60, height/2);
            context.arc(width/2, height/2, 60, 0, 2*Math.PI, true)
            context.fill();
            context.stroke();

            // Draw some text
            context.beginPath();
            context.strokeStyle = "lime green"
            context.font = "20px sans-serif";
            context.text("Hello, world!", width/2, 50);
            context.stroke();
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
