#ifndef MCLDIALOG_H
#define MCLDIALOG_H

#include <QDialog>

namespace Ui {
class MCLDialog;
}

class MCLDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MCLDialog(QWidget *parent = 0);
  void setAugmentParameterBox(double a_fast, double a_slow);
  void setWeightParameterBox(double wvis, double wcmps);
  ~MCLDialog();

signals:
  void resetParticles(bool,double,double,double);
  void setParameter(double,double,double);
  void setAugmentParameter(double,double);
  void setWeightParameter(double,double);
private:
  Ui::MCLDialog *ui;
};

#endif // MCLDIALOG_H
