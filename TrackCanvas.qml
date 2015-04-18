import QtQuick 2.0

import com.elmsoft.qmlcomponents 1.0

Canvas {
    anchors.fill: parent

    property QtObject lineModel: null

    property int baseLength: 200

    Connections {
        target: lineModel
        onModelChanged: requestPaint()
    }

    onPaint: {
        // Get drawing context
        var context = getContext("2d");

        // Make canvas all white
        context.beginPath();
        context.clearRect(0, 0, width, height);
        context.fill();

        if (lineModel === null)
        {
            return
        }

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
        context.moveTo(width/2 + baseLength, height/2 + 150)
        context.lineTo(width/2 + baseLength - 30, height/2 + 150)
        context.moveTo(width/2 - baseLength, height/2 + 150)
        context.lineTo(width/2 - baseLength + 30, height/2 + 150)
        context.stroke();

        context.beginPath()
        context.strokeStyle = lineModel.sectionColour(3)
        context.moveTo(width/2 + baseLength - 30, height/2 + 150)
        context.lineTo(width/2 - baseLength + 30, height/2 + 150)
        context.stroke()

        // RH Outer points
        context.beginPath();
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)

        context.moveTo(width/2 + baseLength - 30, height/2 + 150)
        context.lineTo(width/2 + baseLength, height/2 + 180)
        context.stroke()

        // LH Outer points
        context.beginPath();
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)

        context.moveTo(width/2 - baseLength + 30, height/2 + 150)
        context.lineTo(width/2 - baseLength, height/2 + 180)
        context.stroke()

        // Station outer points
        context.beginPath();
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)
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
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)
        context.moveTo(width/2 + baseLength - 60, height/2 + 120)
        context.lineTo(width/2 + baseLength - 90, height/2 + 90)
        context.stroke()
        context.beginPath();
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)
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
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)
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
        context.strokeStyle = lineModel.controllerColour(LineStateModel.eNoController)
        context.moveTo(width/2 + baseLength - 60, height/2 + 120)
        context.lineTo(width/2 + baseLength - 30, height/2 + 120)
        context.lineTo(width/2 + baseLength + 30, height/2 + 60)
        context.stroke()

        // RH Sidings lower
        context.beginPath();
        context.strokeStyle = lineModel.sectionColour(11)
        context.moveTo(width/2 + baseLength - 30, height/2 + 120)
        context.lineTo(width/2 + baseLength + 60, height/2 + 120)
        context.stroke()

        // RH Sidings middle
        context.beginPath();
        context.strokeStyle = lineModel.sectionColour(12)
        context.moveTo(width/2 + baseLength , height/2 + 90)
        context.lineTo(width/2 + baseLength + 70, height/2 + 90)
        context.stroke()

        // RH Sidings upper
        context.beginPath();
        context.strokeStyle = lineModel.sectionColour(13)
        context.moveTo(width/2 + baseLength + 30, height/2 + 60)
        context.lineTo(width/2 + baseLength + 80, height/2 + 60)
        context.stroke()
    }
}
