#ifndef WEBCLIENTWORKER_H
#define WEBCLIENTWORKER_H

#include <QObject>

class WebClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit WebClientWorker(QObject *parent = nullptr);

signals:
};

#endif // WEBCLIENTWORKER_H
