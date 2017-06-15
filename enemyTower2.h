#ifndef ENEMYTOWER2_H
#define ENEMYTOWER2_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QPointF>
#include<QObject>
#include<QTimer>

class enemyTower2: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    enemyTower2 (QGraphicsItem * parent=0);

    QGraphicsPolygonItem * attack_area;

    QPointF attack_dest;

    double distance_to(QGraphicsItem * item);

    void attack_target();
    bool target_exist ;
    int hp;
    QTimer * timer = new QTimer();
    QTimer * timerd = new QTimer();
    ~enemyTower2();

public slots:
    void dead();
    void acquire_target();


};

#endif // ENEMYTOWER2_H
