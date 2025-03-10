#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QStringList>
#include <QThread>
#include <QtSvg/QSvgRenderer>

class backend : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QStringList logList READ logList WRITE setLogList NOTIFY logListChanged FINAL)
    Q_PROPERTY(QString qrCode READ qrCode WRITE setQrCode NOTIFY qrCodeChanged FINAL)

public:

    explicit backend(QObject *parent = nullptr);
    QStringList logList();
    QString qrCode();
    void setLogList(QStringList);
    void setQrCode(QString);
    void test();
    void pushLog(QString log_string);

    void setLocalIp(QString localIp);
    void setPort(QString port);

    // set functions for server running flags
    void setBackendServerRunning(bool running);
    void setClinetServerRunning(bool running);
signals:

    void logListChanged();
    void qrCodeChanged(QString svg);
    void serversInitializationSucces(QThread::Priority priority);
    void clientRunning();
    void backendRunning();
    void remoteAddressAvaliable(QString address);

public slots:

    void callMe();


private:

    QStringList m_logList;
    QString m_qrCode;
    bool m_backendRunning;
    bool m_clientRunning;
    QString m_localIp;
    QString m_port;
};

#endif // BACKEND_H
