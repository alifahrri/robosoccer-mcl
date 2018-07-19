#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>

class Robot : public QGraphicsItem
{
public:
    Robot();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setPos(double x, double y, double w);
    void setVel(double vx, double vy, double w);
    void setColor(QColor color) { robot_color = color; }
    double getAngle() { return angle; }
    QVector<QLineF> getScanlines() { return scanlines; }
    QPointF getPos() { return pos; }

private:
    QPointF pos;
    double angle;
    QLineF line_angle;
    QVector<QLineF> scanlines;
    QColor robot_color;
};

#endif // ROBOT_H
