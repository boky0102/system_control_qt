#include "capture.h"
#include <QObject>

Capture::Capture(QObject *parent) :
    QObject(parent)
{

}

bool Capture::running()
{
    return m_running;
}

void Capture::setRunning(bool captureRunning)
{
    m_running = captureRunning;
}
