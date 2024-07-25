#ifndef _CODE_HANDLER_H
#define _CODE_HANDLER_H

#include <QSettings>
#include <QCryptographicHash>
#include <QDebug>
#include "qaesencryption.h"

//后期如果要考虑复杂跨平台场景 我们可以优先考虑用策略模式加配置文件的形式或者说用qt自身插件机制进行优化

class CodeHandler //加密解密类
{
public:
    CodeHandler();
    ~CodeHandler();
    QString EncryptCode(const QString data);
    QString DecryptCode(const QString data);
private:
    QByteArray key;
    QSettings * KeyContext;
    QAESEncryption * Encryption;
};

#endif
