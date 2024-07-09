import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id:myWindow //此控件因为qt版本过低，没有其他方法实现全屏，只能用组件构造方法
    visible: true
    width: 640
    height: 480

    //flags: Qt.FramelessWindowHint //设置无标题窗口
    title: qsTr("餐饮窗口")

    Component.onCompleted: {
//        myWindow.showFullScreen(); //全屏幕 测试时候关闭 上线时候打开
    }
}
