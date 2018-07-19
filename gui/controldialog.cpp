#include "controldialog.h"
#include "ui_controldialog.h"

ControlDialog::ControlDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ControlDialog)
{
  ui->setupUi(this);
  connect(ui->setpos_btn,&QPushButton::clicked,[=]{
    double x = ui->xpos_spinbox->value();
    double y = ui->ypos_spinbox->value();
    double w = ui->wpos_spinbox->value();
    emit setPos(x*100,y*100,w);
  });
  connect(ui->setvel_btn,&QPushButton::clicked,[=]{
    double vx = ui->vx_spinbox->value();
    double vy = ui->vy_spinbox->value();
    double vw = ui->vw_spinbox->value();
    emit setVel(vx,vy,vw);
  });
  setFixedSize(size());
  setWindowTitle("Sim Parameter");
}

ControlDialog::~ControlDialog()
{
  delete ui;
}

