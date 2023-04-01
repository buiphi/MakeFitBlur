import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

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
            fileDialog.folder = fileDialog.shortcuts.pictures
            fileDialog.selectFolder = false
            fileDialog.selectMultiple = true
            fileDialog.open()
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose files"
        folder: shortcuts.pictures
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        selectMultiple: true
        onAccepted: {
            if(fileDialog.selectFolder)
                controller.save(fileDialog.folder)
            else
                controller.open(fileDialog.fileUrls)
        }
        onFolderChanged: {
            console.log("onFolderChanged " + folder)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

    TextField{
        id: txtRadius
        y: 50
        text: imageModel.radius
        horizontalAlignment: Text.AlignRight
        validator: IntValidator {bottom: 1; top: 1000000000}
        selectByMouse: true
    }

    Text{
        y: 50
        font.pixelSize: 30
        text: "Radius: "
    }

    Button{
        text: "save"
        objectName: "save"
        enabled: imageModel.total != 0 && imageModel.total > imageModel.completeTotal
        y : 100
        onClicked: {
            fileDialog.folder = fileDialog.shortcuts.pictures
            fileDialog.selectFolder = true
            fileDialog.open()
        }
    }

    Text{
        y: 150
        text: "Total: " + imageModel.total
    }

    Text {
        y: 200
        text: "Completed: " + imageModel.completeTotal
    }
}
