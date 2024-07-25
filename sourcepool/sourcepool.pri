#可以尝试在不使用redis的情况下 自定义一个内存数据库

INCLUDEPATH += ../sourcepool
DEPENDPATH += ../sourcepool

HEADERS += \
        $$PWD/source.h   \
        $$PWD/sourceQueue.h

SOURCES += \
        $$PWD/source.cpp   \
        $$PWD/sourceQueue.cpp
