#ifndef FIELD_H
#define FIELD_H

#define FIELD_WIDTH 900
#define FIELD_HEIGHT 600

#define XLINE1 450
#define XLINE2 XLINE1-38
#define XLINE3 XLINE1-113
#define XLINE4 0
#define XLINE5 -(XLINE3)
#define XLINE6 -(XLINE2)
#define XLINE7 -(XLINE1)

#define YLINE1 300
#define YLINE2 213
#define YLINE3 138
#define YLINE4 -(YLINE3)
#define YLINE5 -(YLINE2)
#define YLINE6 -(YLINE1)

#define CENTER_RADIUS 100

#include <QGraphicsItem>

class Field : public QGraphicsItem
{
public:
    Field();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QVector<QLineF> getLines() { return lines; }
    QVector<QLineF> getCircleLine() { return circle_lines; }

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QVector<QLineF> lines;
    QVector<QLineF> circle_lines;
    QRectF center_circle;
};

#endif // FIELD_H
