#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGamepadManager>
#include <QTimer>
#include <cmath>
#include <random>
#include <iostream>

#define TO_RADIAN M_PI/180.0

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  field(new Field),
  robot(new Robot),
  robot_estimate(new Robot),
  robot_weighted_estimate(new Robot),
  whites(new WhitePoints),
  mcl_item(new MCLItem(mcl)),
  control_dialog(new ControlDialog(this)),
  mcl_dialog(new MCLDialog(this)),
  sensor_viewer(new SensorView(this)),
  distance_matrix(new DistanceMatrix(*(mcl.getField()),this)),
  timer(new QTimer())
{
  ui->setupUi(this);
  ui->graphicsView->setScene(new QGraphicsScene(field->boundingRect(),this));
  ui->graphicsView->scene()->addItem(field);
  ui->graphicsView->scene()->addItem(whites);
  ui->graphicsView->scene()->addItem(mcl_item);
  ui->graphicsView->scene()->addItem(robot);
  ui->graphicsView->scene()->addItem(robot_estimate);
  ui->graphicsView->scene()->addItem(robot_weighted_estimate);
  ui->graphicsView->setBackgroundBrush(Qt::black);
  ui->graphicsView->scale(0.8,0.8);
  ui->graphicsView->setRenderHint(QPainter::Antialiasing);

  mcl_dialog->setAugmentParameterBox(mcl.get_a_fast(), mcl.get_a_slow());
  mcl_dialog->setWeightParameterBox(mcl.get_w_vis(), mcl.get_w_cmps());

  // prepare gamepad
  QGamepadManager *joy_manager = QGamepadManager::instance();
  if(joy_manager->connectedGamepads().size()) {
    gamepad = new QGamepad(joy_manager->connectedGamepads().front());
    connect(timer,&QTimer::timeout,[=]{
      double vx = gamepad->axisLeftX();
      double vy = gamepad->axisLeftY();
      double w = gamepad->axisRightX();
      emit this->control_dialog->setVel(vx,vy,w);
    });
  }

  connect(ui->actionSensor_View,&QAction::toggled,[=](bool checked)
  {
    if(checked && !sensor_viewer->isVisible())
      sensor_viewer->show();
    else if(!checked && sensor_viewer->isVisible())
      sensor_viewer->hide();
  });
  connect(ui->actionMCL_Dialog,&QAction::toggled,[=](bool checked)
  {
    if(checked && !mcl_dialog->isVisible())
      mcl_dialog->show();
    else if(!checked && mcl_dialog->isVisible())
      mcl_dialog->hide();
  });
  connect(mcl_dialog,&QDialog::finished,[=](int result)
  {
    this->ui->actionMCL_Dialog->blockSignals(true);
    this->ui->actionMCL_Dialog->setChecked(false);
    this->ui->actionMCL_Dialog->blockSignals(false);
  });
  connect(ui->actionControl_Dialog,SIGNAL(changed()),this,SLOT(toggleDialog()));
  connect(control_dialog,&QDialog::finished,[=](const int result){
    this->ui->actionControl_Dialog->blockSignals(true);
    this->ui->actionControl_Dialog->setChecked(false);
    this->ui->actionControl_Dialog->blockSignals(false);
  });
  connect(ui->actionDistance_Matrix,&QAction::toggled,[=](bool checked)
  {
    if(checked && !distance_matrix->isVisible())
      distance_matrix->show();
    else if(!checked && distance_matrix->isVisible())
      distance_matrix->hide();
  });
  connect(distance_matrix,&QDialog::finished,[=]
  {
    this->ui->actionDistance_Matrix->blockSignals(true);
    this->ui->actionDistance_Matrix->setChecked(false);
    this->ui->actionControl_Dialog->blockSignals(false);
  });
  connect(control_dialog,&ControlDialog::setPos,[=](double x, double y, double w){
    this->robot->setPos(x,y,w);
    checkLinePoints();
  });
  connect(control_dialog,&ControlDialog::setVel,[=](double vx, double vy, double vw){
    this->robot->setVel(vx,vy,vw);
    mcl.updateMotion(vx,vy,vw);
    auto mcl_sensor_data = checkLinePoints();
    mcl.updateCompass(robot->getAngle());
    mcl.updateSensor(mcl_sensor_data);
    auto estimation = mcl.estimation();
    auto weighted_estimation = mcl.weighted_estimation();
    robot_estimate->setPos(std::get<0>(estimation),
                           std::get<1>(estimation),
                           std::get<2>(estimation));
    robot_weighted_estimate->setPos(std::get<0>(weighted_estimation),
                                    std::get<1>(weighted_estimation),
                                    std::get<2>(weighted_estimation));
    std::cout << "robot->getAngle() : " << robot->getAngle() << "; "
              << "std::get<2>(estimation) : " << std::get<2>(estimation) << "; "
              << "mcl.cmps : " << mcl.getCompass()
              << std::endl;
  });
  connect(mcl_dialog,&MCLDialog::resetParticles,[=](bool init, double x, double y, double w)
  {
    mcl.resetParticles(init,x,y,w);
    mcl_item->update();
  });
  connect(mcl_dialog,&MCLDialog::setParameter,[=](double xvar, double yvar, double wvar)
  {
    mcl.setRandomParameter(xvar,yvar,wvar);
  });
  connect(mcl_dialog,&MCLDialog::setAugmentParameter,[=](double a_fast, double a_slow)
  {
    mcl.setAugmentParam(a_fast,a_slow);
  });
  connect(mcl_dialog,&MCLDialog::setWeightParameter,[=](double w_vis, double w_cmps)
  {
    mcl.setCmpsWeight(w_cmps);
  });
  robot_estimate->setColor(Qt::yellow);
  robot_weighted_estimate->setColor(Qt::white);
  setCentralWidget(ui->graphicsView);
  setWindowTitle("MCL Test");
  this->timer->start(30);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::toggleDialog()
{
  if(!ui->actionControl_Dialog->isChecked())
  {
    if(control_dialog->isVisible())
      control_dialog->hide();
  }
  else
  {
    if(!control_dialog->isVisible())
      control_dialog->show();
  }
}

std::vector<MCL::SensorData> MainWindow::checkLinePoints()
{
  QVector<QLineF> field_lines = field->getLines();
  QVector<QLineF> field_center = field->getCircleLine();
  QVector<QLineF> robot_scanlines = robot->getScanlines();
  QVector<QPointF> white_point;
  QVector<QPointF> white_points_robot;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<double> xrg(0.0,10.0), yrg(0.0,10.0), angle_rg(0.0,5.0);
  for(auto& line : robot_scanlines)
  {
    QPointF intersection_point;
    for(auto& l : field_lines)
    {
      if(line.intersect(l,&intersection_point)==QLineF::BoundedIntersection)
      {
        white_point.push_back(intersection_point);
        QPointF p_robot = intersection_point-robot->getPos();
        double robot_angle = robot->getAngle()+angle_rg(gen);
        double c = cos(robot_angle*TO_RADIAN);
        double s = sin(robot_angle*TO_RADIAN);
        QPointF p;
        p.setX(c*p_robot.x()-s*p_robot.y()+xrg(gen));
        p.setY(s*p_robot.x()+c*p_robot.y()+yrg(gen));
        white_points_robot.push_back(p);
      }
    }
    for(auto& l : field_center)
    {
      if(line.intersect(l,&intersection_point)==QLineF::BoundedIntersection)
      {
        white_point.push_back(intersection_point);
        QPointF p_robot = intersection_point-robot->getPos();
        double robot_angle = robot->getAngle()+angle_rg(gen);
        double c = cos(robot_angle*TO_RADIAN);
        double s = sin(robot_angle*TO_RADIAN);
        QPointF p;
        p.setX(c*p_robot.x()-s*p_robot.y()+xrg(gen));
        p.setY(s*p_robot.x()+c*p_robot.y()+yrg(gen));
        white_points_robot.push_back(p);
      }
    }
  }
  std::vector<MCL::SensorData> mcl_sensor_data;
  for(const auto& p : white_points_robot)
    mcl_sensor_data.push_back(MCL::SensorData(p.x(),p.y()));
  mcl_item->update();
  sensor_viewer->setData(white_points_robot);
  white_points = white_point;
  whites->setWhites(white_points);
  return mcl_sensor_data;
}
