import QtQuick 2.0
import QtGraphicalEffects 1.12
import QtQuick.Window 2.12

Window {
    x: 0
    y: 0
    visible: true
    maximumHeight: 5000
    maximumWidth: 5000
    width: imageModel.width
    height: originImage.height

    onHeightChanged: {
        console.log("onHeightChanged " + height)
    }

    title: imageModel.source
    objectName: "window"

    FastBlur {
        id: blur
        width: imageModel.width
        height: imageModel.height
        anchors.verticalCenter: parent.verticalCenter

        source : originImage
        radius: imageModel.radius

    }
    Image{
        id: originImage
        source: imageModel.source
        anchors.centerIn: blur
    }
}
