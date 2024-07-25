import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Core.MachineControl 1.0


//机械控制界面
Item {
    id:machine

    MachineControl{
        id:controlDevice
    }

    Rectangle//背景虚化
    {
        width:parent.width
        height:parent.height
        color: "white"
        opacity:0.6
    }

    Rectangle
    {
        width:300
        height: 300
        color: "black"
        anchors.centerIn: parent
        radius: 20
        opacity: 0.7

        Button{
            height: 50
            width: 50
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: 20
            text: qsTr("关机")

            background:Rectangle {
                radius:25
                color:"lightblue"
            }

            onClicked: {
                    controlDevice.setPower(0,0)
            }
        }

        Button{
            height: 50
            width: 50
            anchors.centerIn: parent
            text: qsTr("睡眠")

            background:Rectangle {
                radius:25
                color:"lightblue"
            }

            onClicked: {
                 controlDevice.setPower(1,0)
            }
        }

        Button{
            height: 50
            width: 50
            text:qsTr("重启")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20

            background:Rectangle {
                radius:25
                color:"lightblue"

            }

            onClicked: {
                 controlDevice.setPower(2,0)
            }
        }

        Button{
             width: 50
             height: 50
             anchors.bottom: parent.bottom
             anchors.horizontalCenter: parent.horizontalCenter
             anchors.bottomMargin: 20
             text: qsTr("退出")

             background:Rectangle {
                 radius:25
                 color:"lightblue"

             }

             onClicked: {
                machine.visible = false;
             }
        }

   }

   Component.onCompleted: {
       console.log("Machine load Complete")
   }
}
