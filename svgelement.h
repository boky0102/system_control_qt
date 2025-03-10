#ifndef SVGELEMENT_H
#define SVGELEMENT_H

#include <QQuickPaintedItem>
#include <QSvgRenderer>

class SvgElement : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QByteArray svgSource READ svgSource WRITE setSource NOTIFY SourceChanged FINAL)
public:
    SvgElement(QQuickPaintedItem* parent = nullptr);
    void paint(QPainter *painter) override;
    QByteArray svgSource();
    void setSource(QByteArray &source);
signals:
    void SourceChanged(QByteArray src);
private:
    QSvgRenderer *m_renderer;
    QByteArray svgSoruce;
};

#endif // SVGELEMENT_H
