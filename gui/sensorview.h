#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include <QDialog>
#include <QGraphicsItem>

namespace Ui {
class SensorView;
}

class SensorView : public QDialog
{
    Q_OBJECT

public:
    typedef std::pair<double,double> SensorData;
    explicit SensorView(QWidget *parent = 0);
    ~SensorView();
    void setData(const QVector<QPointF> &data);
    void setData(const std::vector<SensorData> &data);


private:
    class SensorItem : public QGraphicsItem
    {
    public:

        SensorItem();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;
        void setData(const std::vector<SensorData> &data_);
    private:
        std::vector<SensorData> data;
    };

private:
    Ui::SensorView *ui;
    SensorItem* sensor_item;
};

#endif // SENSORVIEW_H
