#ifndef CONTROLDIALOG_H
#define CONTROLDIALOG_H

#include <QDialog>

namespace Ui {
class ControlDialog;
}

class ControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControlDialog(QWidget *parent = 0);
    ~ControlDialog();

signals:
    void setPos(double,double,double);
    void setVel(double,double,double);

private:
    Ui::ControlDialog *ui;
};

#endif // CONTROLDIALOG_H
