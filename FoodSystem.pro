QT += quick core gui widgets sql network quickcontrols2 serialport serialbus charts multimedia

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

LIBS += -lcrypto

RESOURCES += qml.qrc \
    mainWidget.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /interfacefunction/machine.qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

#核心类注入目录
include(./core/core.pri)
#系统日志目录
include(./systemlog/systemLog.pri)
#通讯模块
include(./network/network.pri)
#默认配置模块
include(./defaultconfig/defaultconfig.pri)
#资源池
include(./sourcepool/sourcepool.pri)
#串口通信
include(./port/port.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#此方法无法胜任精确定位错误要求 后期有时间可以具体看看是否存在使用不当
unix:!macx: LIBS += -L$$PWD/Breakpad/ -lqBreakpad

INCLUDEPATH += $$PWD/Breakpad/include
DEPENDPATH += $$PWD/Breakpad/include

unix:!macx: PRE_TARGETDEPS += $$PWD/Breakpad/libqBreakpad.a
