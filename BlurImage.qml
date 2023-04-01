import QtQuick 2.0
import QtGraphicalEffects 1.12
import QtQuick.Window 2.12

Window {
    x: 0
    y: 0
    visible: true
    maximumHeight: 1440
    maximumWidth: 2560
    width: myImage.width
    height: originImage.height

    onHeightChanged: {
        console.log("onHeightChanged " + height)
    }

    title: myImage.source
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
