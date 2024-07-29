import QtQuick 2.12
import QtQuick.Controls 2.12

Button{
    id:myButton
    width: parent.width
    property var btnRadius: 0 //自行设计是否圆边
    property var widgetIndex: -1 //页面索引
    opacity: myButton.hovered ? 0.7 : 0.3
    property alias backgroundBtn: background

    background: Rectangle{
        id:background
        color: myButton.hovered ? "orange" : "white"
    }

}
