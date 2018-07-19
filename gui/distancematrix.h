#ifndef DISTANCEMATRIX_H
#define DISTANCEMATRIX_H

#include <QDialog>
#include "mcl.h"

namespace Ui {
class DistanceMatrix;
}

class QGraphicsPixmapItem;

class DistanceMatrix : public QDialog
{
    Q_OBJECT

public:
    explicit DistanceMatrix(MCL::FieldMatrix& field_, QWidget *parent = 0);
    ~DistanceMatrix();

private:
    void showEvent(QShowEvent *event);
    void calculateField();

private:
    Ui::DistanceMatrix *ui;
    MCL::FieldMatrix& field;
    QGraphicsPixmapItem* pixmap_item;
};

#endif // DISTANCEMATRIX_H
