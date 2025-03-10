#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QHostAddress>
#include <QNetworkInterface>

#include "backend.h"
#include "serverworker.h"
#include "webclientworker.h"
#include "qrgenerator.h"
#include "svgelement.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    backend backend;
    SvgElement svgElement;

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    qmlRegisterType<SvgElement>("SvgElement", 1, 0, "SvgElement");
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backend", &backend);
    rootContext->setContextProperty("qrCode", &svgElement);
    engine.loadFromModule("untitled1", "Main");


    ////////////// GET IP ADDRESS ////////////////////////
    QString localAddress = "";
    const QHostAddress &localHost = QHostAddress(QHostAddress::LocalHost);
    for(const auto& address: QNetworkInterface::allAddresses()){
        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != localHost){
            qDebug() << "Local ip adress is : " << address;
            localAddress = address.toString();
            backend.setLocalIp(localAddress);
        }
    }
    //////////////////////////////////////////////////////





    //////////// BACKEND STARTUP ////////////////////
    ServerWorker* serverWorker = new ServerWorker(&backend);
    QThread *backendThread = new QThread();
    serverWorker->moveToThread(backendThread);
    QObject::connect(backendThread, &QThread::started, serverWorker, [serverWorker](){
        serverWorker->startServer();
    });
    QObject::connect(backendThread, &QThread::finished, backendThread, &QThread::deleteLater);
    QObject::connect(backendThread, &QThread::finished, serverWorker, &QWebSocketServer::deleteLater);
    ////////////////////////////////////////////////


    //////////// FRONTEND CLIENT ///////////////////
    WebClientProcess *webClientWorker = new WebClientProcess(&backend);
    webClientWorker->startWebClient();
    QObject::connect(&app, &QGuiApplication::aboutToQuit, webClientWorker, &WebClientProcess::killProcess);
    ////////////////////////////////////////////////

    /////////// QR CODE CREATION //////////////////
    QRGenerator* qrGenerator = new QRGenerator(&backend, &svgElement);
    QThread* qGeneratorThread = new QThread();

    QObject::connect(&backend, &backend::serversInitializationSucces, qGeneratorThread, &QThread::start);
    QObject::connect(qGeneratorThread, &QThread::started, qrGenerator, [qrGenerator, &backend, &localAddress, &webClientWorker](){
        auto qrSVG = qrGenerator->generateSvgQrCode("http://" + localAddress + ":" + webClientWorker->getPort() + "/3003");
        backend.setPort(webClientWorker->getPort());
        backend.setQrCode(qrSVG);
    });
    QObject::connect(qGeneratorThread, &QThread::finished, qrGenerator, &QThread::deleteLater);
    qrGenerator->moveToThread(qGeneratorThread);
    //////////////////////////////////////////////


    /////////// SVG RENDER //////////////////////
    QObject::connect(&svgElement, &SvgElement::SourceChanged, [&](QByteArray source){
        qDebug() << "Tried to push svg to log";
        backend.pushLog("Svg log pushed");
    });
    /////////////////////////////////////////////

    backendThread->start();
    int r = app.exec();

    return r;
}
