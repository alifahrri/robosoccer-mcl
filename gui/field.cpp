#include "field.h"
#include <QPainter>

#define ANGLE_INCREMENT 3

Field::Field()
{
    lines.push_back(QLineF(QPointF(XLINE1,YLINE1),
                           QPointF(XLINE7,YLINE1)));
    lines.push_back(QLineF(QPointF(XLINE1,YLINE6),
                           QPointF(XLINE7,YLINE6)));
    lines.push_back(QLineF(QPointF(XLINE1,YLINE1),
                           QPointF(XLINE1,YLINE6)));
    lines.push_back(QLineF(QPointF(XLINE7,YLINE1),
                           QPointF(XLINE7,YLINE6)));
    lines.push_back(QLineF(QPointF(XLINE4,YLINE1),
                           QPointF(XLINE4,YLINE6)));
    lines.push_back(QLineF(QPointF(XLINE2,YLINE3),
                           QPointF(XLINE2,YLINE4)));
    lines.push_back(QLineF(QPointF(XLINE6,YLINE3),
                           QPointF(XLINE6,YLINE4)));
    lines.push_back(QLineF(QPointF(XLINE3,YLINE2),
                           QPointF(XLINE3,YLINE5)));
    lines.push_back(QLineF(QPointF(XLINE5,YLINE2),
                           QPointF(XLINE5,YLINE5)));
    lines.push_back(QLineF(QPointF(XLINE2,YLINE3),
                           QPointF(XLINE1,YLINE3)));
    lines.push_back(QLineF(QPointF(XLINE2,YLINE4),
                           QPointF(XLINE1,YLINE4)));
    lines.push_back(QLineF(QPointF(XLINE3,YLINE2),
                           QPointF(XLINE1,YLINE2)));
    lines.push_back(QLineF(QPointF(XLINE3,YLINE5),
                           QPointF(XLINE1,YLINE5)));

    lines.push_back(QLineF(QPointF(XLINE6,YLINE3),
                           QPointF(XLINE7,YLINE3)));
    lines.push_back(QLineF(QPointF(XLINE6,YLINE4),
                           QPointF(XLINE7,YLINE4)));
    lines.push_back(QLineF(QPointF(XLINE5,YLINE2),
                           QPointF(XLINE7,YLINE2)));
    lines.push_back(QLineF(QPointF(XLINE5,YLINE5),
                           QPointF(XLINE7,YLINE5)));

    center_circle.setLeft(-CENTER_RADIUS);
    center_circle.setTop(-CENTER_RADIUS);
    center_circle.setHeight(2*CENTER_RADIUS);
    center_circle.setWidth(2*CENTER_RADIUS);

    QPointF circle_line0(center_circle.width()/2,0.0);
    QLineF line(QPointF(0.0,0.0),circle_line0);
    circle_lines.push_back(QLineF(circle_line0,line.p2()));
    for(int i=ANGLE_INCREMENT; i<=360; i+=ANGLE_INCREMENT)
    {
        line.setAngle(i);
        QPointF p0 = circle_lines.back().p2();
        circle_lines.push_back(QLineF(p0,line.p2()));
    }
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::transparent);
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
    painter->setPen(QPen(Qt::white,3.3));
    painter->setBrush(Qt::transparent);
    painter->drawLines(lines);
    painter->drawEllipse(center_circle);
}

QRectF Field::boundingRect() const
{
    return QRectF(XLINE7-100,YLINE6-100,FIELD_WIDTH+200,FIELD_HEIGHT+200);
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Field::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
