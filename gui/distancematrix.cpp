#include "distancematrix.h"
#include "ui_distancematrix.h"
#include <QGraphicsPixmapItem>
#include <iostream>

#define DISTANCE_MATRIX_WIDTH 1100
#define DISTANCE_MATRIX_HEIGHT 800

DistanceMatrix::DistanceMatrix(MCL::FieldMatrix &field_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DistanceMatrix),
    field(field_)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(-size().width()/2,-size().height()/2,
                                                  size().width(),size().height(),this));
    QImage distance(QSize(DISTANCE_MATRIX_WIDTH,DISTANCE_MATRIX_HEIGHT),QImage::Format_RGB888);
    pixmap_item = ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(distance));
    setFixedSize(size()+QSize(50,50));
    calculateField();
    setWindowTitle(QString("Distance Matrix"));
}

DistanceMatrix::~DistanceMatrix()
{
    delete ui;
}

void DistanceMatrix::showEvent(QShowEvent *event)
{

}

void DistanceMatrix::calculateField()
{
    QImage distance(QSize(DISTANCE_MATRIX_WIDTH,DISTANCE_MATRIX_HEIGHT),QImage::Format_RGB888);
    for(int i=0; i<DISTANCE_MATRIX_WIDTH; i++)
    {
        for(int j=0; j<DISTANCE_MATRIX_HEIGHT; j++)
        {
            auto color = (int)(field.distance((double)i-DISTANCE_MATRIX_WIDTH/2,(double)j-DISTANCE_MATRIX_HEIGHT/2))+50;
            auto px = color>255?255:color<0?0:color;
            QColor c(px,px,px);
            distance.setPixel(QPoint(i,j),c.rgb());
        }
    }
    distance.invertPixels();
    pixmap_item->setPixmap(QPixmap::fromImage(distance.scaledToWidth(ui->graphicsView->scene()->width(),Qt::SmoothTransformation)));
    pixmap_item->setX(-ui->graphicsView->scene()->width()/2);
    pixmap_item->setY(-ui->graphicsView->scene()->height()/2);
}
