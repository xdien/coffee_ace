import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
Item {
    id: prod_item_view
    width: 920
    height: 630

    signal doubleClickItem(string banid)

    ListModel {
        id: fruitModel

        ListElement {
            name: "Apple"
            cost: 2.45
            chiecKhau: 0
            trangThai: true
            gioVao: "11:22:11"
        }
        ListElement {
            name: "Orange"
            cost: 3.25
        }
        ListElement {
            name: "Banana"
            cost: 1.95
        }
    }

    Component {
        id: fruitDelegate
        Item {
            id: itemDel
            width: 150
            height: 150
            Rectangle{
                id: ban
                anchors.fill: parent
               color: TRANG_THAI_TRONG?"red":"blue"

               RowLayout{
                   //width: parent.width
                   anchors.bottom: parent.bottom

                   Text {
                       id: banid
                       text: BANID }
                   Text {
                       text: '$' }
               }
               RowLayout{
                   Text {
                       text: qsTr("Gio vao")
                   }
                   Text{
                       text:"a"
                   }
               }
            }
            Image {
                anchors.horizontalCenter: parent.horizontalCenter;
                    width: 100
                    height: 100
                    source: "img/chair.png"
                    Text {
                        text: TEN
                        anchors.centerIn: parent
                    }
                }

            MouseArea{
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: {
                               if (mouse.button == Qt.LeftButton)
                               {
                               }
                               else if (mouse.button == Qt.RightButton)
                               {
                                   contextMenu.open()
                               }
                           }
                onPressAndHold:  prod_item_view.doubleClickItem(banid.text)
            }
            Menu { id: contextMenu

                    MenuItem {
                        text: qsTr('Chuyen Ban')
                    }
                    MenuItem{
                        text: qsTr('In phieu')
                    }
                    MenuItem{
                        text: qsTr('Thanh toan');
                    }
                    MenuItem{
                        text:qsTr("Roi ban");
                    }
                }
        }

    }
    GridView{
        id: gridview
        focus: true
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        flickDeceleration: 750
        maximumFlickVelocity: 1500
        anchors.centerIn: parent
        layoutDirection: Qt.LeftToRight
        flow: GridView.FlowLeftToRight
        boundsBehavior: Flickable.StopAtBounds
        snapMode: GridView.SnapToRow
        anchors.fill: parent
        anchors.margins: 20
        delegate: fruitDelegate
        model: phieuXuatModel
        cellWidth: 158
        cellHeight: 158
    }
}
//It is possible for roles to contain list data. In the following example we create a list of fruit attributes:

/*ListModel {
    id: fruitModel

    ListElement {
        name: "Apple"
        cost: 2.45
        attributes: [
            ListElement { description: "Core" },
            ListElement { description: "Deciduous" }
        ]
    }
    ListElement {
        name: "Orange"
        cost: 3.25
        attributes: [
            ListElement { description: "Citrus" }
        ]
    }
    ListElement {
        name: "Banana"
        cost: 1.95
        attributes: [
            ListElement { description: "Tropical" },
            ListElement { description: "Seedless" }
        ]
    }
}*/
