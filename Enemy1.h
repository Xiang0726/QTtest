#ifndef ENEMY1_H
#define ENEMY1_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include"Bullet1.h"
#include<QTimer>
class Enemy1 : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT


public:
    Enemy1(QGraphicsItem * parent=0);
    QGraphicsPolygonItem *attack_area;
    int team;
    int hp;
    void hpdecreace();
    void attack();
    QPointF target;
    bool has;
    ~Enemy1();

    QTimer * move_timer = new QTimer(this);
public slots:
    void move();

};
#endif // ENEMY1_H
