import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Core.Context 1.0
import Core.MachineControl 1.0
import Config.Right 1.0

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

    ConfigRight{
         id:rightManager
     }

    Context{
        id:deviceControl
    }

    property var rightRegister:rightManager.flag
    property var btnName: rightManager.btnNames

    Loader{
           id:myLoader
           anchors.fill: parent// 弹出的界面都布满全局
           sourceComponent: orderPage
    }

    //登录页面-Component
    Component{
           id:loginPage
           MyWidget.LoginWidget {

                btnClick.onClicked: {
                    deviceControl.setMethod("User");
                    let infoList = ["username",userText,passText]
                    var right = deviceControl.loginVerity(infoList)

                    if(right >= 0)
                    {
                       rightManager.flag = right
                       myLoader.sourceComponent = workPage
                    }
                }
           }

    }

    Component{
        id:workPage
        MyWidget.WorkBench{
        }
    }

    Component{
        id:dataPage
        MyWidget.DataWidget{
        }
    }

    Component{
        id:orderPage
        MyWidget.OrderManagement{
        }
    }

    Component{
        id:typePage
        MyWidget.SortManagement{
        }
    }

    Component{
        id:staffPage
        MyWidget.StaffManagement{
        }
    }

    Component{
        id:classifyPage
        MyWidget.ClassifyWidget{
        }
    }

    Image{
        z:100
        x:parent.width - width
        source: "qrc:/icon/system.png"
        MouseArea{
            id:btnOpen
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

    Drawer {
         id: pageList
         z:100
         width: 160
         height: parent.height
         Image {
             anchors.fill: parent
             source: "qrc:/icon/nature.jpg"
             fillMode: Image.PreserveAspectCrop
         }

         Column {
             width: parent.width
             height:parent.height
             spacing: 20

             Repeater{
                 model:btnName
                 delegate: CustomControl.CustomButton{
                     height: 30
                     text: qsTr(btnName[index])
                     anchors.horizontalCenter: parent.horizontalCenter

                     widgetIndex:index

                     onClicked: {
                         loadWidget(widgetIndex)
                     }
                 }

            }
       }
     }

    Image {
        source: "../icon/home"
        opacity: 0.5
        z:100
        MouseArea{
            anchors.fill: parent
            onClicked:{
                pageList.open()
            }
        }
    }


    Component.onCompleted: {
//        myWindow.showFullScreen(); //全屏幕 测试时候关闭 上线打包时候解除注释
    }

    function loadWidget(index)
    {
        if(rightRegister<0)
            return
         switch(index)
         {
             case 0:
                 myLoader.sourceComponent = workPage
                 break;
             case 1:
                 myLoader.sourceComponent = dataPage
                 break;
             case 2:
                 myLoader.sourceComponent = orderPage
                 break;
             case 3:
                 myLoader.sourceComponent = typePage
                 break;
             case 4:
                 myLoader.sourceComponent = staffPage
                 break;
             case 5:
                 myLoader.sourceComponent = classifyPage
                 break;
         }
    }
}
