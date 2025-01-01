#include "serverworker.h"
#include <QWebSocketServer>
#include <QDebug>
#include <QObject>
#include <QWebSocket>
#include <mouse.h>

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
}

void ServerWorker::onNewConnection()
{
    QWebSocket *pSocket = m_server->nextPendingConnection();
    if(pSocket == nullptr){
        m_backend->pushLog("New connection can't be established");
        return;
    }

    m_backend->pushLog("Socket connection established");

    QObject::connect(pSocket, &QWebSocket::textMessageReceived, this, &ServerWorker::handleMessage);
    QObject::connect(pSocket, &QWebSocket::disconnected, this, &ServerWorker::handleSocketDisconnect);
}



void ServerWorker::handleMessage(QString message)
{
    m_backend->pushLog("Recieved data on socket : " + message);

    auto strings = message.split("/");
    int x = strings[0].toInt();
    int y = strings[1].toInt();
    Mouse::MoveCursor(x, y);
}

void ServerWorker::handleSocketDisconnect()
{
    m_backend->pushLog("Disconnected socket");
}

