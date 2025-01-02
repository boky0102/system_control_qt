#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QThread>
#include <backend.h>
#include <QWebSocketServer>

enum MsgType{
    MOUSE_MOV = '0',
    MOUSE_DOUBLE_CLICK ='1',
    MOUSE_CLICK = '2',
    MOUSE_SCROLL = '3',
    KEYBOARD = '4',
    SHUTDOWN = '5',
    VOLUME = '6'
};

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(backend *backend, QObject* parent = nullptr);

public slots:
    void startServer();
private slots:
    void onNewConnection();

    // Each message recieved is handled based on custom txt format which looks like MsgType!Data/MoreData/MoreData
    void handleMessage(QString message);
    void handleSocketDisconnect();
private:

    // socket message handlers
    void handleMouseMove(QString &message);
    void handleMosueClick(QString &message);
    void handleMosueDoubleClikc(QString &message);
    void handleVolumeChange(QString &message);
    void handleShutDown(QString &message);


    backend* m_backend;
    QWebSocketServer* m_server;
};

#endif // SERVERWORKER_H
