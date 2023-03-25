import QtQuick 2.0
import QtGraphicalEffects 1.12
import QtQuick.Window 2.12

Window {
    x: 0
    y: 0
    visible: true
    maximumHeight: 5000
    maximumWidth: 5000
    width: myImageWidth
    height: myImage.height
    onHeightChanged: {
        console.log("Phi: onHeightChanged " + height)
    }

    title: qsTr("Blur Image")
    objectName: "window"
    FastBlur {
        width: myImageWidth
        height: myImageHeight
        anchors.verticalCenter: parent.verticalCenter

        source : myImage
        radius: myRadius

        Image{
            id: myImage
            source: myImageSource
            anchors.centerIn: parent
            smooth: true
        }

        Component.onCompleted: {
            console.log("onCompleted " + myImageSource)
        }
    }
}
