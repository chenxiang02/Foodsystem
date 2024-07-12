import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Core.Context 1.0
import "./interfacefunction" as MyWidget


//版本支持度差 后期优化难度大 如有条件使用6以上版本

Window {
    id:myWindow //此控件因为qt版本过低，没有其他方法实现全屏，只能用组件构造方法
    visible: true
    width: 640
    height: 480
    //flags: Qt.FramelessWindowHint //设置无标题窗口
    title: qsTr("餐饮窗口")

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/icon/sky.png"
    }

    ColumnLayout{
        anchors.fill: parent;
        Rectangle{
            Layout.alignment: Qt.AlignHCenter
            radius:5
            implicitWidth:  parent.width > 760 ? parent.width / 2 - 90 : 320
            implicitHeight: parent.height > 560 ? parent.height / 2 - 60 : 280
            opacity:0.7

            ColumnLayout{
                anchors.fill: parent
                Label{
                    color: "black"
                    text: qsTr("登陆")
                    Layout.alignment: Qt.AlignHCenter
                    opacity: 1


                }

                TextField{
                    id:userName
                    Layout.alignment: Qt.AlignHCenter
                    implicitWidth: parent.width / 2 + 30
                    implicitHeight: 30
                    placeholderText:"账户"

                    background: Rectangle{
                         color:"white"
                         border.width: userName.hovered ? 3 : 0
                         border.color: "lightgreen"
                         radius: 3
                    }
                }

                TextField{
                    id:passWord
                    Layout.alignment: Qt.AlignHCenter
                    implicitWidth: parent.width / 2 + 30
                    implicitHeight: 30
                    placeholderText:"密码"
                    echoMode:"Password"

                    background: Rectangle{
                         color:"white"
                         border.width: passWord.hovered ? 3 : 0
                         border.color: "lightgreen"
                         radius: 3
                    }
                }

                Button{
                    id:login
                    implicitWidth: 50
                    implicitHeight: 50
                    text: qsTr("登陆")




                    NumberAnimation on implicitWidth {
                        from: 50
                        to:200
                        duration: 300
                        running: login.hovered
                    }

                    NumberAnimation on implicitWidth {
                        from: 200
                        to:50
                        duration: 300
                        running: !login.hovered
                    }

                    Layout.alignment: Qt.AlignHCenter
                    background: Rectangle{
                        radius: login.height / 2
                        gradient: Gradient{
                            GradientStop{position: 0.0;color: "lightpink"}
                            GradientStop{position: 1.0;color:"lightblue"}
                        }
                    }
                    onClicked: {
                        if(!machine.visible) //如果系统控制能显示 则禁用此功能
                        {
                            let apiMethod = new Context;
                            apiMethod.setMethod("User")
                            let InfoList = [userName.text,passWord.text]
                            apiMethod.applyFindData(1,InfoList)
                        }
                    }
                }
            }
        }
    }

    Image {
        x:parent.width - width
        source: "qrc:/icon/system.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                 machine.visible = true
            }
        }
    }

    MyWidget.Machine{
        id:machine
        width: parent.width
        height: parent.height
        visible: false
    }


    Component.onCompleted: {
//        myWindow.showFullScreen(); //全屏幕 测试时候关闭 上线打包时候解除注释
    }
}
