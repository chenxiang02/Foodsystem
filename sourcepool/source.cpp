#include "source.h"

Source::Source()
{
    this->memory = new QSharedMemory;

    this->memory->setKey("MenuList");

    this->MemorySize = 4096;//默认创建4096
    qDebug()<<Q_FUNC_INFO<<"构造空间大小为:"<<this->MemorySize<<"(Byte)";

    this->memory->create(this->MemorySize);
    if(this->memory->error() == QSharedMemory::AlreadyExists)
        qDebug()<<Q_FUNC_INFO<<"默认区域已经被创建";

    qDebug()<<Q_FUNC_INFO<<"source类构造(默认空间构造)";
}

Source::Source(QString MemoryAddress,int MemorySize)
    :MemoryAddress(MemoryAddress),MemorySize(MemorySize)
{
    this->memory = new QSharedMemory;

    this->memory->setKey(MemoryAddress);

    this->memory->create(MemorySize);
    if(this->memory->error()== QSharedMemory::AlreadyExists)
        qDebug()<<Q_FUNC_INFO<<"默认区域已被创建";

    qDebug()<<Q_FUNC_INFO<<"构造空间大小为:"<<this->MemorySize<<"(Byte)";


    qDebug()<<Q_FUNC_INFO<<"source类构造(自定义分配空间)";
}

Source::~Source()
{
    qDebug()<<Q_FUNC_INFO<<"source类析构";
}

QString Source::readMenuContext()
{
    this->memory->attach();//进入共享空间

    char *date = static_cast<char *>(this->memory->data());

    QString readDate(date);

    memset(date,0,this->memory->size());

    this->memory->detach();//脱离共享受空间

    return readDate;
}

void Source::writeMenuContext(QString date)
{
    this->memory->lock();//上锁

    this->memory->attach();//进入共享空间

    char * memoryDate = static_cast<char *>(this->memory->data());

    strcpy(memoryDate,date.toUtf8().data());//将信息写入内存.

    this->memory->detach();//脱离共享空间

    this->memory->unlock();//解锁
}

void Source::DestoryMemory()
{
    this->memory->destroyed();
}
