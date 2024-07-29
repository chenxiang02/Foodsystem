import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import Config.MenuDetail 1.0

ScrollView{
    clip: true

    MenuDetail{
        id:menuData
    }

    property var menuList: menuData.menu

    Column{
        Repeater{
            model: menuList
            delegate: Repeater{
                model: menuList[index]
                delegate: Item{
                    Label{
                        text: qsTr(menuList[index][index])
                    }
                }
            }
        }
    }
}
