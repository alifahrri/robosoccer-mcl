#include "sensorview.h"
#include "ui_sensorview.h"

SensorView::SensorView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorView),
    sensor_item(new SensorItem)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(-size().width()/2,-size().height()/2,
                                                  size().width(),size().height(),this));
    ui->graphicsView->scene()->addItem(sensor_item);

    setWindowTitle(QString("Sensor Viewer (Local)"));
    setFixedSize(size()+QSize(50,50));
}

SensorView::~SensorView()
{
    delete ui;
}

void SensorView::setData(const QVector<QPointF> &data)
{
    std::vector<SensorData> sensor;
    for(const auto &d : data)
        sensor.push_back(SensorData(d.x(),d.y()));
    sensor_item->setData(sensor);
}

void SensorView::setData(const std::vector<SensorView::SensorData> &data)
{
    sensor_item->setData(data);
    sensor_item->update();
}

SensorView::SensorItem::SensorItem()
{

}

void SensorView::SensorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto matrix = painter->matrix();
    painter->setPen(Qt::red);
    painter->drawEllipse(QPointF(0.0,0.0),5.0,5.0);
    painter->drawLine(QPointF(0.0,0.0),QPointF(7.0,0.0));
    painter->setPen(Qt::green);
    painter->setBrush(Qt::green);
    for(const auto& d : data)
    {
        painter->setMatrix(matrix);
        painter->translate(d.first,d.second);
        painter->drawEllipse(QPointF(0.0,0.0),3.3,3.3);
    }
}

QRectF SensorView::SensorItem::boundingRect() const
{
    return QRectF(-450,-300,900,600);
}

void SensorView::SensorItem::setData(const std::vector<SensorView::SensorData> &data_)
{
    data = data_;
    update();
}
