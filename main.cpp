#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <Controller.h>
#include <QQmlContext>

#include <iostream>
#include <csignal>
#include "Logger.h"


void sig_handler(int signum){
    switch (signum) {
    case SIGTERM:
        qDebug() << "Error: SIGTERM";
        break;
    case SIGSEGV:
        qDebug() << "Error: SIGSEGV";
        break;
    case SIGINT:
        qDebug() << "Error: SIGINT";
        break;
    case SIGILL:
        qDebug() << "Error: SIGILL";
        break;
    case SIGABRT:
        qDebug() << "Error: SIGABRT";
        break;
    case SIGFPE:
        qDebug() << "Error: SIGFPE";
        break;
    default:
        qDebug() << "undefine";
        break;
    }
}


int main(int argc, char *argv[])
{
    signal(SIGTERM, sig_handler);
    signal(SIGSEGV, sig_handler);
    signal(SIGINT,  sig_handler);
    signal(SIGILL,  sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGFPE,  sig_handler);


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    ImageModel imageModel;
    Controller controller(&imageModel, &engine);

    engine.load(url);

    return app.exec();
}
