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

    //设置默认风格
//    QQuickStyle::setStyle("Fusion");

    QBreakpadHandler a;
    a.setDumpPath("crash");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
    engine.addImportPath("./interfacefunction/");
    engine.load(url);

    return app.exec();
}
