import QtQuick 2.12
import QtQuick.Controls 2.12

Item{
    Image {
        source: "../icon/home"
        opacity: 0.5
        signal mySignal
        MouseArea{
            anchors.fill: parent
            onClicked:{
                pageList.open()
            }
        }
    }
    Text{
        anchors.centerIn: parent
        text: qsTr("人员");
    }
}
