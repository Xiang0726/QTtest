#ifndef TBULLET1_H
#define TBULLET1_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include<QTimer>
class TBullet1: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    TBullet1(QGraphicsItem * parent=0);
    QTimer * move_timer = new QTimer(this);
    ~TBullet1();
    int from;

public slots:
    void move();
};
#endif // TBULLET1_H
