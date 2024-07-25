import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Item{

    //列文本属性
    property alias columnTextOne: colTextOne
    property alias columnTextTwo: colTextTwo

    //行文本属性
    property alias rowTextOne: rowTextOne
    property alias rowTextTwo: rowTextTwo

    //自定义控件背景色
    property alias backgroundColor: background

    //选择行或列布局
    property var rowOrcolumn:false

    Rectangle{
        id:background
        anchors.fill: parent
        opacity: 0.8
    }

    Column{
        spacing: 10
        visible:!rowOrcolumn
        anchors.centerIn: parent
        Text {
            id: colTextOne
            text: qsTr("text")
            visible:!rowOrcolumn
        }

        Text {
            id: colTextTwo
            text: qsTr("text")
            visible:!rowOrcolumn
        }
    }

    Row{
        spacing: 10
        visible: rowOrcolumn
        anchors.centerIn: parent
        Text{
            id:rowTextOne
            text: qsTr("text")
            visible: rowOrcolumn
        }
        Text{
            id:rowTextTwo
            text: qsTr("text")
            anchors.bottom: rowTextOne.bottom
            anchors.bottomMargin: 5
            visible: rowOrcolumn
        }
    }

}
