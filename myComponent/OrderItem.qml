import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Item{
    width: 300
    height: 50

    property alias orderLabel: orderText
    property alias timeLabel: timeText
    property alias totalLabel: totalText

    property alias detailbtn: detailBtn
    property alias cancelbtn: cancelBtn

    Rectangle{
        id:background
        anchors.fill: parent

    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            background.color = "#FFFD99"
        }
        onExited: {
            background.color = "white"
        }
    }

    Label{
        id:orderText
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("text")
    }
    Label{
        id:timeText
        anchors.left: orderText.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("text")
    }
    Label{
        id:totalText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Button{
        id:detailBtn
        anchors.right: cancelBtn.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("详细信息")
        background: Rectangle{
            color:detailBtn.hovered ? "#00F5FF" : "white"
            border.color: detailBtn.hovered ? "white" : "black"
            border.width:  1
        }
    }
    Button{
        id:cancelBtn
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("取消")
        background: Rectangle{
            color:cancelBtn.hovered ? "#00F5FF" : "white"
            border.color: cancelBtn.hovered ? "white" : "black"
            border.width:  1
        }
    }
}
