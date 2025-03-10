#include "backend.h"
#include <QDebug>
#include <QStringListModel>

backend::backend(QObject *parent)
    : QObject{parent},
    m_logList{},
    m_qrCode{}
{
    qDebug() << "State created";
    m_backendRunning = false;
    m_clientRunning = false;
}

QStringList backend::logList()
{
    return m_logList;
}

QString backend::qrCode()
{
    return m_qrCode;
}

void backend::setLogList(QStringList list)
{
    m_logList = list;
}

void backend::setQrCode(QString qrCode)
{
    m_qrCode = qrCode;
    qrCodeChanged(qrCode);
}

void backend::pushLog(QString log_string)
{
    qDebug() << "Got log -> " << log_string;
    m_logList.append(log_string);
    logListChanged();
}

void backend::setLocalIp(QString localIp)
{
    m_localIp = localIp;
}

void backend::setPort(QString port)
{
    m_port = port;
    emit remoteAddressAvaliable(m_localIp + ":" + m_port);
}

void backend::setBackendServerRunning(bool running)
{
    m_backendRunning = running;
    emit backendRunning();
    if(m_backendRunning && m_clientRunning){
        serversInitializationSucces(QThread::NormalPriority);
        pushLog("Both servers started successfuly");
        qDebug() << m_localIp + ":" + m_port;
    }
}

void backend::setClinetServerRunning(bool running)
{
    m_clientRunning = running;
    emit clientRunning();
    if(m_backendRunning && m_clientRunning){
        serversInitializationSucces(QThread::NormalPriority);
        pushLog("Both servers started succesfully");
        qDebug() << m_localIp + ":" + m_port;
    }

}


void backend::callMe()
{
    qDebug() << "I am being called";
    m_logList.append("Added one");
    logListChanged();
}
