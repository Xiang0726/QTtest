#ifndef BULLET2_H
#define BULLET2_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy1.h"
#include<QTimer>
class Bullet2: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet2(QGraphicsItem * parent=0);
    QTimer * move_timer = new QTimer(this);
    ~Bullet2();

public slots:
    void move();
};

#endif // BULLET2_H
