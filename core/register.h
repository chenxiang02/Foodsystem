#ifndef _REGISTER_H
#define _REGISTER_H

#include <QtQml>

class Register
{
private:
    Register();

public:
    //注意此类用于注入元对象类
    static void registerClass();
};

#endif
