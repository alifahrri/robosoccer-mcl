#include "whitepoints.h"
#include <QPainter>

WhitePoints::WhitePoints()
{

}

void WhitePoints::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::red);
    painter->drawPoints(whites.data(),whites.size());
    painter->setPen(Qt::gray);
    for(auto& w : whites)
        painter->drawEllipse(w,3.0,3.0);
}

QRectF WhitePoints::boundingRect() const
{
    return QRectF(-450,-300,900,600);
}
