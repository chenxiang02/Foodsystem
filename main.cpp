#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCryptographicHash>
#include <QQuickStyle>

#include "core/register.h"

#include "core/CodeHandler.h"

#include <Breakpad/include/QBreakpadHandler.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Register::registerClass();//调用注册类方法

    Register::regiseterServe();//注册服务器(尽量不使用在同一线程或进程下 避免阻塞)

    //设置默认风格
//    QQuickStyle::setStyle("Fusion");

    //错误定位
//    QBreakpadHandler a;
//    a.setDumpPath("crash");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.addImportPath("./interfacefunction/");
    engine.load(url);

    return app.exec();
}
