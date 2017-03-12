import QtQuick 2.0

Item {
    id: item1
    Text {
        id: text1
        x: 0
        y: 136
        width: 150
        height: 14
        text: qsTr("Gio vao")
        font.pixelSize: 12
    }

    Text {
        id: text2
        x: 53
        y: 68
        text: qsTr("Ten ban").TEN
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        z: 1
        font.pixelSize: 12
    }

    Image {
        id: image1
        x: 25
        y: 8
        width: 100
        height: 100
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Text {
        id: text3
        x: 0
        y: 116
        width: 150
        height: 14
        text: qsTr("So tien")
        font.pixelSize: 12
    }

    Text {
        id: text4
        x: 0
        y: 0
        text: qsTr("ma ban").BANID
        font.pixelSize: 12
    }

}
