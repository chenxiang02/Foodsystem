#ifndef _RIGHT_CONFIG_H
#define _RIGHT_CONFIG_H

#include <QSettings>
#include <QObject>
#include <QDebug>

class RightConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int flag READ getFlag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(QStringList btnNames READ getBtnNames WRITE setBtnNames NOTIFY btnNamesChanged)
public:
    RightConfig();
    ~RightConfig();

    int getFlag() const;
    void setFlag(int value);

    QStringList getBtnNames() const;
    void setBtnNames(const QStringList &value);

signals:
    void flagChanged();
    void btnNamesChanged();

private:
    int flag;
    QStringList btnNames;
    QSettings * rightSet;

};

#endif
