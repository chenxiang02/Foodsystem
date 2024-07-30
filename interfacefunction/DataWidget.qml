import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Config.DataWidget 1.0
import QtCharts 2.3

Item{

    DataWidget{
        id:dataShow
    }

    property var xAxis: dataShow.Xmax
    property var yAxis: dataShow.Ymax
    property var xyPoint: dataShow.pointValue

    Rectangle{
        anchors.fill: parent
        color: "#F7F8FA"
    }

    Rectangle{
        id:header
        width: parent.width
        height: parent.height / 8
        anchors.top: parent.top
        color: "#F7F8FA"
        Button{
            id:threeDayBtn
            anchors.left: parent.left
            anchors.leftMargin: 40
            width: parent.width / 8
            height: parent.height / 2
            anchors.verticalCenter: parent.verticalCenter
            focus: true
            text: qsTr("近三天")
            background: Rectangle{
                color:threeDayBtn.focus ? "#FEBC04" : "white"
                radius: 5
            }
            onClicked: {
                chartView.title = qsTr("近三日销售额")
                dataShow.setChartUpdate(3)
                lineSeries.clear()
                lineSeries.append(0,0)
                for(let i = 0;i < xyPoint.length;i++)
                {
                    lineSeries.append(i+1,xyPoint[i])
                }
            }
        }
        Button{
            id:sevenDayBtn
            anchors.left: threeDayBtn.right
            anchors.leftMargin: 20
            width: parent.width / 8
            height: parent.height / 2
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("近七天")
            background: Rectangle{
                color:sevenDayBtn.focus ? "#FEBC04" : "white"
                radius: 5
            }
            onClicked: {
                chartView.title = qsTr("近七日销售额")
                dataShow.setChartUpdate(7)
                lineSeries.clear()
                lineSeries.append(0,0)
                for(let i = 0;i < xyPoint.length;i++)
                {
                    lineSeries.append(i+1,xyPoint[i])
                }
            }
        }
        Button{
            id:monthDayBtn
            anchors.left: sevenDayBtn.right
            anchors.leftMargin: 20
            width: parent.width / 8
            height: parent.height / 2
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("近一月")
            background: Rectangle{
                color:monthDayBtn.focus ? "#FEBC04" : "white"
                radius: 5
            }
            onClicked: {
                chartView.title = qsTr("近一月销售额")
                dataShow.setChartUpdate(30)
                lineSeries.clear()
                lineSeries.append(0,0)
                for(let i = 0;i < xyPoint.length;i++)
                {
                    lineSeries.append(i+1,xyPoint[i])
                }
            }
        }
    }

    ChartView
    {
       id: chartView
       title: qsTr("近三日销售额")
       antialiasing: true
       backgroundColor: "lightblue"
       animationOptions: ChartView.SeriesAnimations
       animationDuration: 1
       anchors.top: header.bottom
       width: parent.width
       height: parent.height - header.height

       ValueAxis {
           id: x_axis
           min: 0
           max: xAxis
       }

       ValueAxis {
           id: y_axis
           min: 0
           max: yAxis
       }

       LineSeries {
           id: lineSeries
           axisX: x_axis
           axisY: y_axis

       }
       Component.onCompleted: addSeries(lineSeries)
    }

       function addSeries(lineSeries )
       {
           lineSeries.append(0, 0);
           for(let i = 0;i < xyPoint.length ;i++)
           {
               lineSeries.append(i+1,xyPoint[i])
           }
       }

}
