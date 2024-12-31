#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QStringList>

class backend : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QStringList logList READ logList WRITE setLogList NOTIFY logListChanged FINAL)

public:

    explicit backend(QObject *parent = nullptr);
    QStringList logList();
    void setLogList(QStringList);
    void test();
    void pushLog(QString log_string);

signals:

    void logListChanged();

public slots:

    void callMe();


private:

    QStringList m_logList;
};

#endif // BACKEND_H
