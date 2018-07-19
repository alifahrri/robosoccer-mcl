#ifndef WHITEPOINTS_H
#define WHITEPOINTS_H

#include <QGraphicsItem>

class WhitePoints : public QGraphicsItem
{
public:
    WhitePoints();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setWhites(QVector<QPointF> whites_) { whites = whites_; }

private:
    QVector<QPointF> whites;
};

#endif // WHITEPOINTS_H
