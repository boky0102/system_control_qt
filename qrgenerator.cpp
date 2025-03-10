#include "qrgenerator.h"
#include <sstream>
#include <QDebug>
#include <iostream>
#include <QRegularExpression>
#include <string>

QRGenerator::QRGenerator(backend* backend,SvgElement* svgElement ,QObject *parent)
    : QObject{parent},
    m_backend{backend},
    m_svgElement(svgElement)
{}

QString QRGenerator::generateSvgQrCode(QString text)
{
    auto textString = text.toUtf8();
    qrcodegen::QrCode code = qrcodegen::QrCode::encodeText(textString, qrcodegen::QrCode::Ecc::HIGH);
    std::string svg = toSvgString(code, 3);
    auto svgByte = QByteArray::fromStdString(svg);
    auto svgCopy = QString::fromStdString(svg);

    std::string final = "";

    for(int i = 0; i < svg.size(); i++){
        bool good = true;
        char current = svg[i];
        if(current == '\n' || current == '\t') good = false;
        if(current == '\\') good = false;
        if(good) final.push_back(current);
    }

    std::string finalFinal = "";

    for(int i = 0; i < final.size() - 1; i++){
        char first = final[i];
        char second = final[i + 1];
        if(first == '/' && second == '/'){
            finalFinal.push_back('/');
        } else{
            finalFinal.push_back(final[i]);
        }

        if(i + 1 == final.size() - 2){
            finalFinal.push_back(final[i + 1]);
        }
    }


    m_backend->pushLog("QR code generated");
    m_svgElement->setSource(svgByte);
    return QString::fromStdString(finalFinal);
}

std::string QRGenerator::toSvgString(const qrcodegen::QrCode &qr, int border)
{
    if (border < 0)
        throw std::domain_error("Border must be non-negative");
    if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
        throw std::overflow_error("Border too large");

    std::ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}
