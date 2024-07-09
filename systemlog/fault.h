#ifndef _FAULT_H
#define _FAULT_H

#include "log.h"

class Fault : public Log
{
public:
    Fault();
    ~Fault();
    void printLog(QString info) override;
private:
    QDir * pathDir;
    QFile * writeSuccess;
};

#endif
