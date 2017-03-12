import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
Item {
    id: prod_item_view
    width: 920
    height: 630

    signal doubleClickItem(string banid)
    signal xemPhieu(string pcid)
    signal inVaRoiBan(string pcid)
    Component {
        id: fruitDelegate
        Item {
            id: itemDel
            width: 150
            height: 150

            Rectangle{
                width: parent.width
                height: 100;
                color: TRANG_THAI_TRONG?"#e7e7e7":"#A793EA"
                Text {
                    id: tenBan
                    x: 53
                    y: 68
                    text: TEN
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    z: 1
                    font.pixelSize: 12
                }
                Text {
                    id: phieuXuatId
                    text: PHIEUXUATID
                    visible: false
                }
                Text {
                    id: gioVao
                    x: 0
                    y: 136
                    width: 150
                    height: 14
                    text: GIO_VAO
                    font.pixelSize: 12
                }

            }
            Image {
                id: image1
                x: 25
                y: 8
                width: 100
                height: 100
                source: "qrc:/img/chair.png"
            }

            Text {
                id: tongTien
                x: 0
                y: 116
                width: 150
                height: 14
                text: TRANG_THAI_TRONG?qsTr(""):qsTr("Tổng tiền: "+ TONG_TIEN)
                font.pixelSize: 12
            }

            Text {
                id: banid
                x: 0
                y: 0
                text: BANID
                font.pixelSize: 12
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
                onDoubleClicked: prod_item_view.doubleClickItem(banid.text)
            }
            Menu { id: contextMenu

                MenuItem {
                    text: qsTr('In và rời bàn')
                    onClicked: prod_item_view.inVaRoiBan(phieuXuatId.text)
                }
                MenuItem{
                    text: qsTr('In phieu')
                    onClicked: phieuXuatModel.inBill(phieuXuatId.text);
                }
               /* MenuItem{
                    text:qsTr("Roi ban");
                    onClicked: {

                        //phieuXuatModel.roiBan(banid.text,true)
                    }
                }*/
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
