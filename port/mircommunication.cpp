#include "mircommunication.h"

MirCommunication::MirCommunication()
{
    qDebug()<<Q_FUNC_INFO<<"MirCommunication类构造(虚基类)";
}

MirCommunication::~MirCommunication()
{
    qDebug()<<Q_FUNC_INFO<<"MirCommunication类析构(虚基类)";
}
