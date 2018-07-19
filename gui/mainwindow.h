#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGamepad>
#include "distancematrix.h"
#include "controldialog.h"
#include "field.h"
#include "robot.h"
#include "whitepoints.h"
#include "sensorview.h"
#include "mcl.h"
#include "mclitem.h"
#include "mcldialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void toggleDialog();

private:
    std::vector<MCL::SensorData> checkLinePoints();

private:
    MCL mcl;
    Ui::MainWindow *ui;
    Field *field;
    Robot *robot;
    Robot *robot_estimate;
    Robot *robot_weighted_estimate;
    WhitePoints *whites;
    MCLItem *mcl_item;
    ControlDialog *control_dialog;
    MCLDialog *mcl_dialog;
    SensorView *sensor_viewer;
    DistanceMatrix *distance_matrix;
    QVector<QPointF> white_points;
    QGamepad *gamepad;
    QTimer *timer;
};

#endif // MAINWINDOW_H
