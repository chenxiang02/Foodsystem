#ifndef _SUCCESS_H
#define _SUCCESS_H

#include "log.h"

class Success : public Log
{
public:
    Success();
    ~Success();

    void printLog(QString info) override;
private:
    QDir * pathDir;
    QFile * writeSuccess;
};

#endif
