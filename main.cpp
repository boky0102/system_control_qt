#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

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

    ServerWorker serverWorker(&backend);
    serverWorker.start();

    int r = app.exec();

    return r;
}
