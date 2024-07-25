#ifndef _SOURCE_H
#define _SOURCE_H

#include <QCryptographicHash>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QStringList>
#include <QObject>
#include <QMutex>
#include <QSharedMemory>

extern "C"
{
    #include <string.h>
}

class Source : public QObject
{
    Q_OBJECT
public:
    Source();
    Source(QString MemoryAddress,int MemorySize);
    ~Source();

    QString readMenuContext();//读取默认菜单空间内容
    void writeMenuContext(QString date);

    void DestoryMemory();

private:
    QString MemoryAddress;//指向空间名
    int MemorySize;//空间大小 默认kb
    QSharedMemory * memory;
};

#endif
