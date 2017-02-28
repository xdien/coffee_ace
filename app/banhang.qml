import QtQuick 2.5
Item {
    id: prod_item_view
    width: 920
    height: 630
    ListModel {
        id: fruitModel

        ListElement {
            name: "Apple"
            cost: 2.45
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
            width: 150
            height: 150
            Rectangle{
                anchors.fill: parent
               color: "#ddaa33"
            }
            Row{
                width: parent.width

                Text { text: name
                }
                Text { text: '$' + cost }
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
        model: fruitModel
        cellWidth: 159
        cellHeight: 100
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
