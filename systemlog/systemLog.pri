INCLUDEPATH += ../systemlog
DEPENDPATH += ../systemlog

#当前文件夹下类主要作日志管理使用 用于系统崩溃记录等
HEADERS +=  \
    $$PWD/log.h \
    $$PWD/success.h \
    $$PWD/waring.h\
    $$PWD/fault.h

SOURCES += \
    $$PWD/log.cpp \
    $$PWD/success.cpp \
    $$PWD/waring.cpp\
    $$PWD/fault.cpp
