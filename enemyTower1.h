#ifndef ENEMYTOWER1_H
#define ENEMYTOWER1_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QPointF>
#include<QObject>
#include<QTimer>

class enemyTower1: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    enemyTower1 (QGraphicsItem * parent=0);

    QGraphicsPolygonItem * attack_area;

    QPointF attack_dest;
    QPointF AA;

    double distance_to(QGraphicsItem * item);

    void attack_target();
    bool target_exist ;
    QTimer * timer = new QTimer(this);
    QTimer * timerd = new QTimer(this);
    int hp;
    ~enemyTower1();

public slots:
    void dead();
    void acquire_target();


};
#endif // ENEMYTOWER1_H
