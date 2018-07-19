#ifndef MCLITEM_H
#define MCLITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "mcl.h"

class MCLItem : public QGraphicsItem
{
public:
    MCLItem(MCL& mcl_);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    MCL& mcl;
};

#endif // MCLITEM_H
