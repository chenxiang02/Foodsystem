import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import "../myComponent" as CustomControl
import Config.Work 1.0

Item{
    id:propertyTop
//    clip: true //设置滑动效果

    Work{
        id:workInstantiation
    }

//    Image {
//        anchors.fill: parent
//        source: "qrc:/icon/lake.jpg"
//        fillMode: Image.PreserveAspectCrop
//    }

    property var date:workInstantiation.NowDate

    property var price:workInstantiation.TurnOver
    property var orderCount:workInstantiation.OrderCount
    property var averagePrice: workInstantiation.AveragePrice
    property var orderComplete: workInstantiation.OrderComplete

    property var tobeComplete: workInstantiation.ToBeComplete
    property var finishiOrder: workInstantiation.FinishOrder
    property var cancelOrder: workInstantiation.OrderCancel
    property var allOrder: workInstantiation.AllOrder


    Column{
        anchors.fill: parent
        spacing: 5

        CustomControl.StatusBar{
            implicitWidth: parent.width
            implicitHeight: parent.height / 3

            barTopBtn.text:qsTr("详细数据 >")

            barTopText.rowTextOne.text:qsTr("今日数据")
            barTopText.rowTextTwo.text: qsTr(date)
            barTopText.rowTextOne.font.bold: true
            barTopText.rowTextOne.font.pixelSize: 20

            batBottomItem1.columnTextOne.text: qsTr("营业额")
            batBottomItem1.columnTextTwo.text: qsTr("$ "+price)

            batBottomItem2.columnTextOne.text: qsTr("有效订单")
            batBottomItem2.columnTextTwo.text: qsTr(orderCount)

            batBottomItem3.columnTextOne.text: qsTr("订单完成率")
            batBottomItem3.columnTextTwo.text: qsTr(orderComplete+"%")

            batBottomItem4.columnTextOne.text: qsTr("平均订单价")
            batBottomItem4.columnTextTwo.text: qsTr(averagePrice)
        }

        CustomControl.StatusBar{
            implicitWidth: parent.width
            implicitHeight: parent.height / 3

            barTopText.rowTextOne.text: qsTr("订单管理")
            barTopText.rowTextTwo.text: qsTr(date)
            barTopText.rowTextOne.font.bold: true
            barTopText.rowTextOne.font.pixelSize: 20

            batBottomItem1.columnTextOne.text: qsTr("待出餐")
            batBottomItem1.columnTextTwo.text: qsTr(tobeComplete)

            batBottomItem2.columnTextOne.text: qsTr("已完成")
            batBottomItem2.columnTextTwo.text: qsTr(finishiOrder)

            batBottomItem3.columnTextOne.text: qsTr("已取消")
            batBottomItem3.columnTextTwo.text: qsTr(cancelOrder)

            batBottomItem4.columnTextOne.text: qsTr("全部订单")
            batBottomItem4.columnTextTwo.text: qsTr(allOrder)
        }

        CustomControl.StatusBar{
            implicitWidth: parent.width
            implicitHeight: parent.height / 3

            barTopText.rowTextOne.text: qsTr("菜品总揽")
            barTopText.rowTextTwo.text: qsTr("")
            barTopText.rowTextOne.font.bold: true
            barTopText.rowTextOne.font.pixelSize: 20

            batBottomItem1.columnTextOne.text: qsTr("已启售")
            batBottomItem1.columnTextTwo.text: qsTr(tobeComplete)

            batBottomItem2.columnTextOne.text: qsTr("已停售")
            batBottomItem2.columnTextTwo.text: qsTr(finishiOrder)

            batBottomItem3.columnTextOne.text: qsTr("套餐启售")
            batBottomItem3.columnTextTwo.text: qsTr(cancelOrder)

            batBottomItem4.columnTextOne.text: qsTr("套餐停售")
            batBottomItem4.columnTextTwo.text: qsTr(allOrder)
        }

    }

    Component.onCompleted: {
        console.log("WorkBench loaded complete")
    }
}
