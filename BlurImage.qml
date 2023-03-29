import QtQuick 2.0
import QtGraphicalEffects 1.12
import QtQuick.Window 2.12

Window {
    x: 0
    y: 0
    visible: true
    maximumHeight: 5000
    maximumWidth: 5000
    width: myImage.width
    height: originImage.height
    onHeightChanged: {
        console.log("Phi: onHeightChanged " + height)
    }

    title: qsTr("Blur Image")
    objectName: "window"

    FastBlur {
        width: myImage.width
        height: myImage.height
        anchors.verticalCenter: parent.verticalCenter

        source : originImage
        radius: myImage.radius

        Image{
            id: originImage
            source: myImage.source
            anchors.centerIn: parent
        }
    }
}
