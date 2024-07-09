#ifndef _WARING_H
#define _WARING_H

#include "log.h"

class WaringInfo : public Log
{
public:
    WaringInfo();
    ~WaringInfo();

    void printLog(QString info) override;
private:
    QDir * pathDir;
    QFile * writeSuccess;
};

#endif
