import QtQuick 2.12
import QtQuick.Controls 2.12
import "../myComponent" as CustomControl
import QtQuick.Layouts 1.3
import Config.TypeMenu 1.0

Item{

    TypeMenu{
        id:controlType
    }

    Rectangle{
        anchors.fill: parent
        color: "#F7F8FA"
    }

    property var defaultStr: "text"
    property var foodList: controlType.food
    property var typeList: controlType.TypeList


    Rectangle{
        id:header
        anchors.top: parent.top
        width: parent.width
        height: parent.height / 9
        TextField{
            id:textFind
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.verticalCenter: parent.verticalCenter
            height: 40
            placeholderText: qsTr("请输入菜名")
        }

        Button{
            id:currentBtn
            anchors.left: textFind.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text: qsTr("搜索")
            onClicked: {
                if(textFind.text === "")
                    return
                controlType.findFood(textFind.text)
            }
        }

        Button{
            id:addBtn
            anchors.left: currentBtn.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text: qsTr("添加菜品")
            onClicked: {
                addFood.visible = true
            }
        }
        Button{
            id:btnshow
            anchors.left: addBtn.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text: qsTr("查看所有菜品")
            onClicked: {
                controlType.showAll()
                textFind.text = qsTr("")
            }
        }

    }

    ListView{
        anchors.top: header.bottom
        anchors.topMargin: 10
        width: parent.width
        height: parent.height - header.height
        clip: true
        model: foodList.length / 4
        spacing:10

        delegate: CustomControl.OrderItem{
            width: header.width
            height: 50
            orderLabel.text: qsTr(foodList[index * 4])
            timeLabel.text: qsTr(foodList[index * 4 + 2])
            totalLabel.text: qsTr(foodList[index * 4 + 3])

            detailbtn.text: qsTr("修改")
            cancelbtn.text: qsTr("删除")

            cancelbtn.onClicked: {
                controlType.deleteFood(orderLabel.text)
            }

            detailbtn.onClicked: {
                updateComponent.visible = true
                updateFoodName.text = qsTr("菜品:"+foodList[index * 4])
                updatePrice.placeholderText = qsTr("当前价格为:"+foodList[index * 4 + 3])
                let status = controlType.typeMap(foodList[index * 4 + 2])
                updateStatus.placeholderText = qsTr("当前状态:"+status)

            }
        }

    }

    Rectangle{
        id:addFood
        anchors.fill: parent
        opacity: 0.7
        color: "white"
        visible: false
        Rectangle{
            anchors.centerIn: parent
            width: 260
            height:280
            color: "black"

            TextField{
                id:foodname
                placeholderText: qsTr("请输入要添加的菜名")
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                background: Rectangle{
                    border.color: foodname.focus ? "lightpink" : "white"
                    border.width: foodname.focus ? 3 : 1
                }
            }


            ComboBox{
                id:type
                anchors.top: foodname.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                model:typeList
                delegate: ItemDelegate{
                    text: qsTr(typeList[index])
                    width: type.width
                    height: 30
                }
            }

            TextField{
                id:price
                placeholderText: qsTr("请输入菜品价格")
                anchors.top: type.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                background: Rectangle{
                    border.color: price.focus ? "lightpink" : "white"
                    border.width: price.focus ? 3 : 1
                }
            }

            Button{
                id:confirm
                text: qsTr("确认")
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                onClicked: {
                    let foodadd = [foodname.text,type.currentText,price.text]
                    controlType.addFood(foodadd)
                    addFood.visible = false
                }
            }

            Button{
                id:cancel
                text: qsTr("退出")
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                onClicked: {
                    addFood.visible = false
                    foodname.text = ""
                    price.text = ""
                }
            }

        }
    }

    Rectangle{
        id:updateComponent
        anchors.fill: parent
        color: "white"
        opacity: 0.6
        visible: false
        Rectangle{
            anchors.centerIn: parent
            width: 240
            height: 260
            color: "black"
            Label{
                id:updateFoodName
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 10
                color: "white"
            }

            TextField{
                id:updatePrice
                anchors.top: updateFoodName.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                placeholderTextColor:"white"
                background: Rectangle{
                    border.color: foodname.focus ? "lightpink" : "white"
                    border.width: foodname.focus ? 3 : 1
                }
            }

            TextField{
                id:updateStatus
                anchors.top: updatePrice.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                placeholderTextColor:"white"
                background: Rectangle{
                    border.color: foodname.focus ? "lightpink" : "white"
                    border.width: foodname.focus ? 3 : 1
                }
            }


            Label{
                id:typePrompt
                anchors.top: updateStatus.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                color: "red"
                font.pixelSize: 20
                font.bold:true
            }

            Timer{
                id:promptTime
                interval: 3000
                repeat: false
                running: false
                onTriggered: {
                    typePrompt.visible = false
                }
            }

            Button{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: 80
                text: qsTr("确认")
                onClicked: {
                    if(updateStatus.text === "" && updatePrice.text === "")
                    {
                        typePrompt.text = qsTr("请输入要修改内容")
                        typePrompt.visible = true
                        promptTime.running = true
                        return
                    }

                    let modifyData = [updateFoodName.text.substring(3,12),updatePrice.text,updateStatus.text,]
                    controlType.modifyFood(modifyData)
                    updateComponent.visible = false
                }
            }
            Button{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 20
                text: qsTr("退出")
                width: 80
                onClicked: {
                    updateComponent.visible = false
                }
            }
        }
    }


    Component.onCompleted: {
        controlType.getFoods()
    }
}
