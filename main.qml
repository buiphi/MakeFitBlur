import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Make Fit Blur Image")
    objectName: "window"

    Button{
        text: "open"
        objectName: "button"
        onClicked: {
            controller.open()
        }
    }

    TextField{
        id: txtRadius
        y: 50
        text: "60"
        horizontalAlignment: Text.AlignRight
    }

    Text{
        y: 50
        font.pixelSize: 30
        text: "Radius: "
    }

    Button{
        text: "save"
        objectName: "save"
        y : 100
        onClicked: {
            controller.save(txtRadius.text)
        }
    }

    Text{
        y: 150
        text: "Total: " + myTotal
    }

    Text {
        y: 200
        text: "Completed: " + myCompleted
    }
}
