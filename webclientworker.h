#ifndef WEBCLIENTWORKER_H
#define WEBCLIENTWORKER_H

#include <QObject>
#include "backend.h"
#include <QProcess>

class WebClientProcess : public QObject
{
    Q_OBJECT
public:
    explicit WebClientProcess(backend *backend, QObject *parent = nullptr);
    QString getPort();
public slots:
    void startWebClient();
    void handleErrorOccured(QProcess::ProcessError error);
    void handleOutputReady();
    void killProcess();
signals:

private:
    backend* m_backend;
    QProcess* m_process;
    QString m_port;
};

#endif // WEBCLIENTWORKER_H
