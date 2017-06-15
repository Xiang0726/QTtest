#ifndef BULLET3_H
#define BULLET3_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy1.h"
#include<QTimer>
class Bullet3: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet3(QGraphicsItem * parent=0);
    QTimer * move_timer = new QTimer(this);
    ~Bullet3();


public slots:
    void move();
};
#endif // BULLET3_H
