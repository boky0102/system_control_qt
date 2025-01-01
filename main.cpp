#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QObject>
#include <QDebug>
#include "backend.h"
#include "serverworker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    backend backend;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("untitled1", "Main");

    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backend", &backend);

    ServerWorker* serverWorker = new ServerWorker(&backend);
    QThread *backendThread = new QThread();
    serverWorker->moveToThread(backendThread);

    QObject::connect(backendThread, &QThread::started, serverWorker, [serverWorker](){
        serverWorker->startServer();
    });

    QObject::connect(backendThread, &QThread::finished, backendThread, &QThread::deleteLater);
    QObject::connect(backendThread, &QThread::finished, serverWorker, &QWebSocketServer::deleteLater);

    backendThread->start();
    int r = app.exec();

    return r;
}
