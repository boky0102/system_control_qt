#ifndef QRGENERATOR_H
#define QRGENERATOR_H

#include <QObject>
#include <qrcodegen.hpp>
#include <backend.h>
#include <svgelement.h>

class QRGenerator : public QObject
{
    Q_OBJECT
public:
    explicit QRGenerator(backend* backend, SvgElement* svgElement ,QObject *parent = nullptr);

public slots:
    QString generateSvgQrCode(QString text);
signals:

private:
    std::string toSvgString(const qrcodegen::QrCode &qr, int border);
    backend* m_backend;
    SvgElement* m_svgElement;
};

#endif // QRGENERATOR_H
