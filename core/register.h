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

    //服务注入类
    static void regiseterServe();

    //资源池进行内容读取 可以考虑用redis
    static void registerSourcePool();
};

#endif
