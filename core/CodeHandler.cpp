#include "CodeHandler.h"

CodeHandler::CodeHandler()
{
    //获取配置操作
    this->KeyContext = new QSettings("./code.ini",QSettings::IniFormat);
    //将读取到内容进行转换
    this->key = QCryptographicHash::hash(KeyContext->value("PrivateKey","ddddddddd").toString().toUtf8(), QCryptographicHash::Md5);

    this->Encryption = new QAESEncryption(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::ZERO);

    qDebug()<<Q_FUNC_INFO<<"CodeHandler类构造";
}

CodeHandler::~CodeHandler()
{
    delete this->KeyContext;
    delete this->Encryption;
    qDebug()<<Q_FUNC_INFO<<"CodeHandler类析构";
}

QString CodeHandler::EncryptCode(const QString data)
{
    qDebug()<<Q_FUNC_INFO;
    QByteArray encodedText = this->Encryption->encode(data.toUtf8(), this->key);
    QString encodeToQString = QString::fromLatin1(encodedText.toBase64());
    return encodeToQString;
}

QString CodeHandler::DecryptCode(const QString data)
{
    qDebug()<<Q_FUNC_INFO;
    QByteArray decodedText = this->Encryption->decode(QByteArray::fromBase64(data.toLatin1()), this->key);
    QString decodeToQString = QString::fromUtf8(decodedText);
    return decodeToQString;
}
