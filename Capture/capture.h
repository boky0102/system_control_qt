#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>

class Capture : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY captureStarted FINAL)

public:
    Capture(QObject *parent = nullptr);
    bool running();
    void setRunning(bool captureRunning);

signals:
    void captureStarted();

private:
    bool m_running;
};

#endif // CAPTURE_H
