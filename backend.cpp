#include "backend.h"
#include <QDebug>
#include <QStringListModel>

backend::backend(QObject *parent)
    : QObject{parent},
    m_logList{}
{
    qDebug() << "State created";
}

QStringList backend::logList()
{
    return m_logList;
}

void backend::setLogList(QStringList list)
{
    m_logList = list;
}

void backend::test()
{

}

void backend::pushLog(QString log_string)
{
    qDebug() << "Got log -> " << log_string;
    m_logList.append(log_string);
    logListChanged();
}


void backend::callMe()
{
    qDebug() << "I am being called";
    m_logList.append("Added one");
    logListChanged();
}
