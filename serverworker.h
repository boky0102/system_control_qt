#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QThread>
#include <backend.h>
#include <QWebSocketServer>

class ServerWorker : public QThread
{
    Q_OBJECT
public:
    ServerWorker(backend *backend);

    void run() override;
    void stopServing();
private slots:
    void onNewConnection();
private:
    backend* m_backend;
};

#endif // SERVERWORKER_H
