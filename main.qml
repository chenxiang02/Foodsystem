import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Core.Context 1.0
import Core.MachineControl 1.0
//import Core.CirThread 1.0

import "./interfacefunction" as MyWidget

import "./myComponent" as CustomControl


//版本支持度差 后期优化难度大 如有条件使用6以上版本

Window {
    id:myWindow //此控件因为qt版本过低，没有其他方法实现全屏，只能用组件构造方法
    visible: true
    width: 640
    height: 480
    //flags: Qt.FramelessWindowHint //设置无标题窗口
    title: qsTr("餐饮窗口")
    property var rightValue: -1

//    CirThread{
//        id:netThread
//    }

    Context{
        id:deviceControl
    }

    Loader{
           id:myLoader
           anchors.fill: parent// 弹出的界面都布满全局
    }

       // 2. 登录页面-Component
    Component{
           id:loginPage
           MyWidget.LoginWidget {

                btnClick.onClicked: {
                    deviceControl.setMethod("User");
                    let infoList = ["username",userText,passText]
                    var right = deviceControl.loginVerity(infoList)

                    if(right >= 0)
                    {
//                       netThread.start()
                       myWindow.rightValue = right
                       myLoader.sourceComponent = mainPage
                    }
                }
           }

    }

       // 3.主页面-Component
    Component{
         id:mainPage
         MyWidget.MainWidget {
             rightRegister:myWindow.rightValue
         }
    }

    Image{
        z:100
        x:parent.width - width
        source: "qrc:/icon/system.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                 machine.visible = true
            }
        }
    }//系统显示

    CustomControl.Machine{
        id:machine
        width: parent.width
        height: parent.height
        visible: false
    }


    Component.onCompleted: {
        myLoader.sourceComponent = loginPage // 一开始显示登录页面
//        myWindow.showFullScreen(); //全屏幕 测试时候关闭 上线打包时候解除注释
    }
}
