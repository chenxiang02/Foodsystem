INCLUDEPATH += ../core
DEPENDPATH += ../core

#当前文件夹下核心类 主要注入网络通信 数据存储 视觉 警报
HEADERS += \
        $$PWD/register.h \
        $$PWD/MachineControl.h \
        $$PWD/PowerControl.h \
        $$PWD/SqlSystem.h \
        $$PWD/usr.h \
        $$PWD/food.h \
        $$PWD/account.h

SOURCES += \
        $$PWD/MachineControl.cpp \
        $$PWD/register.cpp \
        $$PWD/PowerControl.cpp\
        $$PWD/SqlSystem.cpp \
        $$PWD/usr.cpp \
        $$PWD/food.cpp \
        $$PWD/account.cpp
