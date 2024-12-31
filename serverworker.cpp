#include "serverworker.h"
#include <QWebSocketServer>
#include <QDebug>

ServerWorker::ServerWorker(backend *backend)
{
    m_backend = backend;
}

void ServerWorker::run()
{
    m_backend->pushLog("Trying to start local socket server");
    QThread::sleep(1);

    auto server = QWebSocketServer("", QWebSocketServer::SslMode::NonSecureMode);
    bool listening = server.listen(QHostAddress::Any);

    if(listening){
        m_backend->pushLog("Scoket server started succesfully");
        auto serverAddress = server.serverAddress();
        auto serverPort = server.serverPort();
        QThread::sleep(1);
        if(serverAddress == QHostAddress::Null){
            m_backend->pushLog("Failed to create socket server");
        }
        m_backend->pushLog("Socket server is listening on address: " + serverAddress.toString());
        QThread::sleep(std::chrono::nanoseconds(100000));
        m_backend->pushLog("Socket server is listening on port :" + QString::number(serverPort));
    }
}

void ServerWorker::onNewConnection()
{

}

// void ServerWorker::stopServing()
// {
//     server.close();
//     qDebug() << "Server closed";
//     m_backend->pushLog("Server is closed");
// }
