#include "robot.h"
#include <cmath>
#include <QPainter>
#include <iostream>

#define ROBOT_RADIUS 20
#define SCAN_RESOLUTION 6
#define TO_RADIAN M_PI/180.0

Robot::Robot() :
    pos(QPointF(0.0,0.0)),
    angle(0.0),
    robot_color(Qt::red)
{
    line_angle.setP1(pos);
    line_angle.setP2(QPoint(ROBOT_RADIUS,ROBOT_RADIUS));
    line_angle.setAngle(angle);
    for(int i=0; i<360; i+=SCAN_RESOLUTION)
    {
        QLineF line(pos,QPointF(0.0,300));
        line.setAngle((double)i+angle);
        scanlines.push_back(line);
    }
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::gray));
//    painter->drawLines(scanlines);
    painter->setPen(QPen(robot_color,2.2));
    painter->setBrush(Qt::transparent);
    painter->drawEllipse(pos,ROBOT_RADIUS,ROBOT_RADIUS);
    painter->drawLine(line_angle);
}

QRectF Robot::boundingRect() const
{
    return QRectF(-450,-300,900,600);
}

void Robot::setPos(double x, double y, double w)
{
    double dx = x-pos.x();
    double dy = y-pos.y();
    pos.setX(x);
    pos.setY(y);
    line_angle.translate(dx,dy);
    line_angle.setAngle(w);
    angle = w;
    double dw = w-angle;
    for(int i=0; i<scanlines.size(); i++)
    {
        scanlines[i].translate(dx,dy);
        scanlines[i].setAngle(scanlines[i].angle()+dw);
    }
    update();
}

void Robot::setVel(double vx, double vy, double w)
{
    double c = cos(angle*TO_RADIAN);
    double s = sin(angle*TO_RADIAN);
    double dx = c*vx+s*vy;
    double dy = -s*vx+c*vy;
    pos.setX(pos.x()+dx);
    pos.setY(pos.y()+dy);
    angle += w;
    while (angle > 360.) {
      angle -= 360.;
    }
    while (angle < 0.) {
      angle += 360.;
    }
    line_angle.translate(dx,dy);
    line_angle.setAngle(angle);
    for(int i=0; i<scanlines.size(); i++)
    {
        scanlines[i].translate(dx,dy);
        scanlines[i].setAngle(scanlines[i].angle()+w);
    }
    // std::cout << "angle : " << angle << std::endl;
    update();
}
