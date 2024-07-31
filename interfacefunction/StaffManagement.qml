import QtQuick 2.12
import QtQuick.Controls 2.12
import "../myComponent" as CustomControl
import QtQuick.Layouts 1.3
import Config.Staff 1.0

Item{
    Staff{
        id:controlStaff
    }

    Rectangle{
        anchors.fill: parent
        color: "#F7F8FA"
    }

    property var defaultStr: "text"

    property var userList: controlStaff.user
    property alias flagValue: controlStaff.flag
    property var alterInfomation: controlStaff.accountText

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
            placeholderText: qsTr("查找员工")
        }

        Button{
            id:currentBtn
            anchors.left: textFind.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text: qsTr("添加")
            onClicked: {
                addPage.visible = true
            }
        }
        Button{
            id:showBtn
            anchors.left: currentBtn.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            height: 36
            width: 115
            text: qsTr("查看所有员工")
            onClicked: {
                controlStaff.getUsers();
            }
        }

    }

    ListView{
        anchors.top: header.bottom
        anchors.topMargin: 10
        width: parent.width
        height: parent.height - header.height
        clip: true
        model: userList.length / 3
        spacing:10

        delegate: CustomControl.OrderItem{
            width: header.width
            height: 50
            orderLabel.text: qsTr(userList[index * 3])
            timeLabel.text: qsTr(userList[index * 3 + 1])
            totalLabel.text: qsTr(userList[index * 3 + 2])

            detailbtn.text: qsTr("修改")
            cancelbtn.text: qsTr("删除")

            cancelbtn.onClicked: {
                controlStaff.deleteUser(orderLabel.text)
            }

            detailbtn.onClicked: {
                controlStaff.accountText = orderLabel.text
                messageWindow.visible = true
            }
        }

    }

    Rectangle{
        id:messageWindow
        anchors.fill:parent
        color: "white"
        opacity: 0.7
        visible: false
        Rectangle{
            anchors.centerIn: parent
            width: 300
            height: 300
            color: "black"

            Label{
                id:account
                text: qsTr("账号:"+alterInfomation)
                color: "white"
                font.pixelSize: 20
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField{
                id:password
                echoMode: "Password"
                placeholderText: qsTr("请输入修改的密码")
                anchors.top: account.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                background: Rectangle{
                    border.color: password.focus ? "lightpink" : "white"
                    border.width: password.focus ? 3 : 1
                }
            }
            TextField{
                id:confirmWord
                echoMode: "Password"
                placeholderText: qsTr("请重新确认要修改密码")
                anchors.top: password.bottom
                width: 200
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle{
                    border.color: confirmWord.focus ? "lightpink" : "white"
                    border.width: confirmWord.focus ? 3 : 1
                }
            }

            Label{
                id:prompt
                text: qsTr("两次密码输入不一致或输入框为空")
                color: "red"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: confirmWord.bottom
                anchors.topMargin: 10
                font.pixelSize: 15
                visible:false
                Behavior on opacity {
                    NumberAnimation{
                        duration: 500
                    }
                }
            }
            Timer{
                id:myTimer
                interval: 3000
                running: false
                repeat: false
                onTriggered: {
                    prompt.visible = false
                }
            }


            Button{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.left: parent.left
                anchors.leftMargin: 20
                text: qsTr("确认")
                background: Rectangle{
                    radius: 5
                }

                onClicked: {
                    if(password.text!==confirmWord.text || password.text==="" || confirmWord.text === "")
                    {
                        prompt.visible = true
                        myTimer.start()
                    }
                    else
                    {
                        let user = [alterInfomation,password.text]
                        controlStaff.setPassWord(user)
                        messageWindow.visible = false
                    }
                }
            }

            Button{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 20
                text: qsTr("退出")
                background: Rectangle{
                    radius: 5
                }
                onClicked: {
                    messageWindow.visible = false
                    password.text = qsTr("")
                    confirmWord.text = qsTr("")
                }
            }
        }
    }

    Rectangle{
        id:addPage
        anchors.fill:parent
        color: "white"
        opacity: 0.8
        visible: false
        Rectangle{
            anchors.centerIn: parent
            color: "black"
            width: 280
            height: 250
            TextField{
                id:inputAccount
                placeholderText: qsTr("输入添加用户名,不可重复")
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                background: Rectangle{
                    border.color: inputAccount.focus ? "lightpink" : "white"
                    border.width: inputAccount.focus ? 3 : 1
                }
            }
            TextField{
                id:inputPassword
                echoMode: "Password"
                placeholderText: qsTr("请输入修改的密码")
                anchors.top: inputAccount.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                background: Rectangle{
                    border.color: inputPassword.focus ? "lightpink" : "white"
                    border.width: inputPassword.focus ? 3 : 1
                }
            }

            TextField{
                id:inputRight
                echoMode: "Password"
                placeholderText: qsTr("请输入用户权限")
                anchors.top: inputPassword.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                visible: controlStaff.flag === 2 ? true : false
                background: Rectangle{
                    border.color: inputRight.focus ? "lightpink" : "white"
                    border.width: inputRight.focus ? 3 : 1
                }
            }

            Label{
                id:promptAdd
                anchors.top: inputRight.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 10
                font.pixelSize: 18
                color: "red"
                visible: false
            }
            Timer{
                id:promptTime
                interval: 3000
                repeat: false
                running: false
                onTriggered: {
                    promptAdd.visible = false
                }
            }

            Button{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 30
                text: qsTr("确认")
                onClicked: {
                    if(inputAccount.text === "" || inputPassword.text === "")
                    {
                        promptAdd.text = qsTr("账户密码输入为空")
                        promptAdd.visible = true
                        promptTime.running = true
                        return;
                    }
                    else if(controlStaff.flag === 1)
                    {
                        let userList = [inputAccount.text,inputPassword.text]
                        controlStaff.addUser(userList)
                        addPage.visible = false
                        inputAccount.text = qsTr("")
                        inputPassword.text = qsTr("")
                        return;
                    }

                    if(controlStaff.flag === 2 && inputRight.text === "" || parseInt(inputRight.text) < 0 || parseInt(inputRight.text) > 1)
                    {
                        promptAdd.text = qsTr("权限输入为空或权限范围过大(0:1)")
                        promptAdd.visible = true
                        promptTime.running = true
                        return;
                    }
                    let userList = [inputAccount.text,inputPassword.text,inputRight.text]
                    controlStaff.addUser(userList)
                    addPage.visible = false
                    inputAccount.text = qsTr("")
                    inputPassword.text = qsTr("")
                    inputRight.text = qsTr("")

                }
            }
            Button{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 30
                text: qsTr("取消")
                onClicked: {
                    addPage.visible = false
                }
            }
        }
    }

    Component.onCompleted: {
        controlStaff.getUsers()
        console.log("StaffManagement.qml loaded")
    }
}
