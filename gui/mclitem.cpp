#include "mclitem.h"

MCLItem::MCLItem(MCL &mcl_) :
    mcl(mcl_)
{

}

void MCLItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto particles = mcl.getParticles();
    auto matrix0 = painter->matrix();
    for(auto p : particles)
    {
        painter->setMatrix(matrix0);
        painter->translate(MCL::x(p), MCL::y(p));
        painter->rotate(-MCL::w(p));
        painter->drawEllipse(QPoint(0,0),3,3);
        painter->drawLine(QPoint(0,0),QPoint(4,0));
    }
}

QRectF MCLItem::boundingRect() const
{
    return QRectF(-450,-300,900,600);
}
