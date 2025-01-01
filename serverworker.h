#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QThread>
#include <backend.h>
#include <QWebSocketServer>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(backend *backend, QObject* parent = nullptr);

public slots:
    void startServer();
private slots:
    void onNewConnection();
    void handleMessage(QString message);
    void handleSocketDisconnect();
private:
    backend* m_backend;
    QWebSocketServer* m_server;
};

#endif // SERVERWORKER_H
