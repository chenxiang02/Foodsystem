import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Config.OrderManage 1.0
import "../myComponent" as CustomControl
Item{

    width: 640
    height: 320

    OrderManage{
        id:controlEvent
    }

    Rectangle{
        anchors.fill: parent
        color: "#F7F8FA"
    }

    property var defaultStr: "text"

    property var dataList:controlEvent.menu
    property var isCurrent: controlEvent.isCurrent
    property var detailMenu: controlEvent.showMenu

    Rectangle{
        id:header
        anchors.top: parent.top
        width: parent.width
        height: parent.height / 9
        TextField{
            id:textFind
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            height: 40
            placeholderText: qsTr("现在显示的是历史账单")
        }

        Button{
            id:findBtn
            anchors.left: textFind.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 80
            text:qsTr("搜索")
            onClicked: {
                controlEvent.findNode(textFind.text)
            }

        }

        Button{
            id:currentBtn
            anchors.left: findBtn.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text: qsTr("查看当前账单")
            onClicked: {
                controlEvent.isCurrent = true
                controlEvent.getCurrentAccount()
                textFind.text = qsTr("")
                textFind.placeholderText = qsTr("现在显示的是当前账单")
            }
        }
        Button{
            id:historyBtn
            anchors.left: currentBtn.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text:qsTr("查看历史账单")
            onClicked: {
                controlEvent.isCurrent = false
                controlEvent.getHistotyAccount()
                textFind.text = qsTr("")
                textFind.placeholderText = qsTr("现在显示的是历史账单")
            }
        }

    }

    ListView{
        anchors.top: header.bottom
        anchors.topMargin: 10
        width: parent.width
        height: parent.height - header.height
        clip: true
        model: dataList.length / 4
        spacing:10

        delegate: CustomControl.OrderItem{
            width: header.width
            height: 50
            orderLabel.text: qsTr(dataList[index * 4])
            timeLabel.text: qsTr(dataList[index * 4 + 1])
            totalLabel.text: qsTr(dataList[index * 4 + 3])
            cancelbtn.visible: isCurrent

            cancelbtn.onClicked: {
                 controlEvent.cancelEvent(dataList[index * 4 + 1],dataList[index * 4 + 3])
            }

            detailbtn.text: qsTr(isCurrent ? "确认" : "详细信息")

            detailbtn.onClicked: {
                if(!isCurrent)
                {
                    controlEvent.getInformation(dataList[index * 4 + 2])
                    detailmessage.visible = true
                }else{
                    controlEvent.confirmMenu(dataList[index * 4 + 1])
                }
            }
        }

    }

    Rectangle{
        id:detailmessage
        anchors.fill:parent
        color: "white"
        opacity: 0.7
        visible: false
        Rectangle{
            anchors.centerIn: parent
            width: 300
            height: 300
            color: "black"
            ListView{
                clip: true
                anchors.top: parent.top
                width: parent.width
                height: 260
                model:detailMenu.length / 3
                delegate: Item {
                    width: parent.width
                    height: 40
                    Label{
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        text: qsTr(detailMenu.length > 2 ?detailMenu[index *3]:defaultStr)
                    }
                    Label{
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        text: qsTr(detailMenu.length > 2 ?detailMenu[index * 3 + 1]:defaultStr)
                    }
                    Label{
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        text: qsTr(detailMenu.length > 2 ? detailMenu[index * 3 + 2] : defaultStr)
                    }
                }
            }

            Button{
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("确认")
                background: Rectangle{
                    radius: 5
                }

                onClicked: {
                    detailmessage.visible = false
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("OrderManagement loaded")
    }
}
