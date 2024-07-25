import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Config.Right 1.0
import "../myComponent" as CustomControl

Item{
    ConfigRight{
        id:rightManager
    }

    property alias rightRegister: rightManager.flag
    property var btnName: rightManager.btnNames


    Drawer {
        id: pageList
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

   Loader{
       id:pageLoder
       anchors.fill: parent
   }

   Component{
       id:workPage
       WorkBench{

       }
   }

   Component{
       id:orderPage
       OrderManagement{

       }
   }

   Component{
       id:sortPage
       SortManagement{

       }
   }

   Component{
       id:staffPage
       StaffManagement{

       }
   }

   Image {
       source: "../icon/home"
       opacity: 0.5
       MouseArea{
           anchors.fill: parent
           onClicked: {
               pageList.open()
           }
       }
   }

   Component.onCompleted: {
       pageLoder.sourceComponent = workPage
       console.log("MainWidget load Complete")
   }

   function loadWidget(index)
   {
        switch(index)
        {
            case 0:
//                myLoader
                break;
            case 1:
//                myLoader
                break;
            case 2:
//                myLoader
                break;
            case 3:
//                myLoader
                break;
            case 4:
//                myLoader
                break;
        }
   }
}
