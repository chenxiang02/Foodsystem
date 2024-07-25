import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Item{
    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/icon/sky.png"
    }

   property var userText: userName.text
   property var passText: passWord.text
   property alias btnClick: login
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

                }
            }
        }
    }
    Component.onCompleted: {
        console.debug("LoginWidget loaded")
    }
}
