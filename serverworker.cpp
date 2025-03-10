#include "serverworker.h"
#include <QWebSocketServer>
#include <QDebug>
#include <QObject>
#include <QWebSocket>
#include <mouse.h>
#include <keyboard.h>
#include <QProcess>

ServerWorker::ServerWorker(backend *backend, QObject *parent) :
    QObject(parent)
{
    m_backend = backend;
}

void ServerWorker::startServer()
{


    QThread::sleep(1);
    m_server = new QWebSocketServer("", QWebSocketServer::SslMode::NonSecureMode);
    QObject::connect(m_server, &QWebSocketServer::newConnection, this, &ServerWorker::onNewConnection);
    m_backend->pushLog("Trying to start socket server");
    if(!m_server->listen(QHostAddress::Any, 3003)){
        m_backend->pushLog("Server failed to start");
        return;
    }
    QThread::sleep(1);
    auto serverAddress = m_server->serverAddress();
    auto serverPort = m_server->serverPort();

    m_backend->pushLog("Server is running on " + serverAddress.toString() + ":" + QString::number(serverPort));
    m_backend->setBackendServerRunning(true);
}

void ServerWorker::onNewConnection()
{
    QWebSocket *pSocket = m_server->nextPendingConnection();
    if(pSocket == nullptr){
        m_backend->pushLog("New connection can't be established");
        return;
    }

    m_backend->pushLog("Someone connected to the app...");

    QObject::connect(pSocket, &QWebSocket::textMessageReceived, this, &ServerWorker::handleMessage);
    QObject::connect(pSocket, &QWebSocket::disconnected, this, &ServerWorker::handleSocketDisconnect);
}



void ServerWorker::handleMessage(QString message)
{
    auto strings = message.split("!");
    QChar msgType = strings[0][0];
    auto msg = strings[1];

    switch(msgType.unicode()){
        case MsgType::MOUSE_MOV:
            handleMouseMove(msg);
            break;
        case MsgType::MOUSE_DOUBLE_CLICK:
            handleMosueDoubleClikc(msg);
            break;
        case MsgType::MOUSE_CLICK:
            handleMosueClick(msg);
            break;
        case MsgType::VOLUME:
            handleVolumeChange(msg);
            break;
        case MsgType::SHUTDOWN:
            handleShutDown(msg);
            break;
    }
}

void ServerWorker::handleSocketDisconnect()
{
    m_backend->pushLog("Someone disconnected from the app...");
}

void ServerWorker::handleMouseMove(QString &message)
{
    auto data = message.split("/");
    if(data.size() != 2){
        m_backend->pushLog("Wrong data format for mouse movement recieved");
    }

    auto x = data[0].toInt();
    auto y = data[1].toInt();

    Mouse::MoveCursor(x, y);
}

void ServerWorker::handleMosueClick(QString &message)
{
    Mouse::Click();
}

void ServerWorker::handleMosueDoubleClikc(QString &message)
{
    Mouse::Click();
    Mouse::Click();
}

void ServerWorker::handleVolumeChange(QString &message)
{
    if(message == "u"){
        Keyboard::VolumeChange(true);
    }else{
        Keyboard::VolumeChange(false);
    }

}

void ServerWorker::handleShutDown(QString &message)
{
    QProcess::execute("shutdown", {"/s"});
}

