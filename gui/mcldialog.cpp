#include "mcldialog.h"
#include "ui_mcldialog.h"

MCLDialog::MCLDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MCLDialog)
{
  ui->setupUi(this);
  setFixedSize(size());

  connect(ui->reset_btn,&QPushButton::clicked,[=]
  {
    bool init = ui->checkBox->isChecked();
    double x = ui->xpos_spinbox->value();
    double y = ui->ypos_spinbox->value();
    double w = ui->wpos_spinbox->value();
    emit resetParticles(init,x,y,w);
  });
  connect(ui->apply_btn,&QPushButton::clicked,[=]
  {
    double xvar = ui->xvar_spinbox->value();
    double yvar = ui->yvar_spinbox->value();
    double wvar = ui->angle_var_spinbox->value();
    emit setParameter(xvar,yvar,wvar);
  });
  connect(ui->set_augment_btn,&QPushButton::clicked,[=]
  {
    double a_fast = ui->a_fast_sbox->value();
    double a_slow = ui->a_slow_sbox->value();
    emit setAugmentParameter(a_fast,a_slow);
  });
  connect(ui->set_weight_btn,&QPushButton::clicked,[=]
  {
    double w_vis = ui->wvis_sbox->value();
    double w_cmps = ui->wcmps_sbox->value();
    ui->wvis_sbox->setValue(1.-w_cmps);
    emit setWeightParameter(w_vis,w_cmps);
  });
  ui->wvis_sbox->setEnabled(false);
  setWindowTitle("MCL Parameter");
}

void MCLDialog::setAugmentParameterBox(double a_fast, double a_slow)
{
  ui->a_fast_sbox->setValue(a_fast);
  ui->a_slow_sbox->setValue(a_slow);
}

void MCLDialog::setWeightParameterBox(double wvis, double wcmps)
{
  ui->wcmps_sbox->setValue(wcmps);
  ui->wvis_sbox->setValue(wvis);
}

MCLDialog::~MCLDialog()
{
  delete ui;
}
