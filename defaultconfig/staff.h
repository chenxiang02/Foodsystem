#ifndef _STAFF_H
#define _STAFF_H

#include <QObject>
#include <QDebug>
#include "core/usr.h"

class Staff : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int flag READ getFlag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(QStringList user READ getUser WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QString accountText READ getAccountText WRITE setAccountText NOTIFY accountChanged)
public:
    Staff(QObject * parent = nullptr);
    ~Staff();

    Q_INVOKABLE void getUsers();
    Q_INVOKABLE void setPassWord(QStringList arg);
    Q_INVOKABLE void deleteUser(QString data);
    Q_INVOKABLE void addUser(QStringList data);

    int getFlag() const;
    void setFlag(int value);

    QStringList getUser();
    void setUser(const QStringList &value);

    QString getAccountText() const;
    void setAccountText(const QString &value);

signals:
    void flagChanged();
    void userChanged();
    void accountChanged();

private:
    int flag;
    QStringList user;
    QString accountText;

    User * sql;

};

#endif
