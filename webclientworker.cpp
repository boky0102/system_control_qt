#include "webclientworker.h"
#include "QProcess"
#include <QDebug>

WebClientProcess::WebClientProcess(backend *backend,QObject *parent)
    : QObject{parent},
    m_backend{backend}
{
    m_process = new QProcess();
    connect(m_process, &QProcess::errorOccurred, this, &WebClientProcess::handleErrorOccured);
    connect(m_process, &QProcess::readyReadStandardOutput, this, &WebClientProcess::handleOutputReady);
}

QString WebClientProcess::getPort()
{
    return m_port;
}

void WebClientProcess::startWebClient()
{
    m_backend->pushLog("Trying to start client process");
    m_process->start("./sc_backend.exe");
}

void WebClientProcess::handleErrorOccured(QProcess::ProcessError error)
{
    qDebug() << "Process enountered an error";
    switch(error){
        case QProcess::FailedToStart:
            qDebug() << "Failed to start";
            break;
        case QProcess::Crashed:
            qDebug() << "Crashed";
            break;
        case QProcess::Timedout:
            qDebug() << "Timedout";
            break;
        case QProcess::ReadError:
            qDebug() << "Read Error";
            break;
        case QProcess::WriteError:
            qDebug() << "Write error";
            break;
        case QProcess::UnknownError:
            qDebug() << "Unknown error";
            break;
        }
}

void WebClientProcess::handleOutputReady()
{
    auto byteMessage = m_process->readAllStandardOutput();
    m_backend->pushLog(byteMessage);
    if(byteMessage.startsWith("SERVER RUNNING ON PORT")){
        auto messages = byteMessage.split(':');
        if(messages.size() != 2){
            m_backend->pushLog("Client server bad port formating");
            return;
        }

        // process message should look like -- SERVER RUNNING ON PORT:NUMBER
        auto port = messages[1];
        auto portTrimmed = port.trimmed();

        m_port = QString::fromLocal8Bit(portTrimmed);

        qDebug() << "PORT :" << m_port;

        m_backend->pushLog("Client server started running successfuly");
        m_backend->setClinetServerRunning(true);
    }
}

void WebClientProcess::killProcess()
{
    if(m_process->Running){
        m_process->kill();
        }
}
