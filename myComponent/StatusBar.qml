import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Item{

    property alias barTopText: barText //顶部文字
    property alias barTopBtn: barTopBtn //顶部按钮

    property alias batBottomItem1: item1
    property alias batBottomItem2: item2
    property alias batBottomItem3: item3
    property alias batBottomItem4: item4

    Rectangle{
        id:top
        width: parent.width
        height: parent.height / 5 + 20
        CustomItem{
            id:barText
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 5 - 10
//            anchors.baseline: parent.baseline
            height: parent.height
            rowOrcolumn: true
        }
        Button{
            id:barTopBtn
            anchors.right: parent.right
            anchors.rightMargin: 35
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height - 10
            background: Rectangle{
                anchors.fill: parent
                color: "white"
            }
        }
    }

    Rectangle{
        anchors.top: top.bottom
        width: parent.width
        height: parent.height / 5 * 4 - 20
        CustomItem{
            id:item1
            width: parent.width / 4 - 10
            height:parent.height
            anchors.left: parent.left
            anchors.leftMargin: 8
            backgroundColor.color:"#FFFD99"
        }
        CustomItem{
            id:item2
            width: parent.width / 4 - 10
            height:parent.height
            anchors.left: item1.right
            anchors.leftMargin: 8
            backgroundColor.color:"#FFFD99"
        }
        CustomItem{
            id:item3
            width: parent.width / 4 - 10
            height:parent.height
            anchors.left: item2.right
            anchors.leftMargin: 8
            backgroundColor.color:"#FFFD99"
        }
        CustomItem{
            id:item4
            width: parent.width / 4 - 10
            height:parent.height
            anchors.left: item3.right
            anchors.leftMargin: 8
            backgroundColor.color:"#FFFD99"
        }
    }
}
