#include "svgelement.h"
#include <QObject>
#include <QQuickItem>
#include <QDebug>
#include <QByteArray>

SvgElement::SvgElement(QQuickPaintedItem* parent) :
    QQuickPaintedItem(parent)
{
    m_renderer = new QSvgRenderer();
}

void SvgElement::paint(QPainter *painter)
{
    if(!m_renderer->isValid()){
        qDebug() << "Renderer is not valid";
        return;
    }

    qDebug() << "Manged to paint renderer";

    m_renderer->render(painter, boundingRect());
}

QByteArray SvgElement::svgSource()
{
    return svgSoruce;
}

void SvgElement::setSource(QByteArray &source)
{
    svgSoruce = source;

    if(m_renderer->load(source)){
        qDebug() << "Svg parsed";
        update();
    } else{
        qDebug() << "Failed to parse svg";
    }

    emit SourceChanged(source);
}

