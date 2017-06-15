#ifndef BULLET1_H
#define BULLET1_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy1.h"
#include<QTimer>
class Bullet1: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet1(QGraphicsItem * parent=0);
    QTimer * move_timer = new QTimer(this);
    ~Bullet1();

public slots:
    void move();
};
#endif // BULLET1_H
