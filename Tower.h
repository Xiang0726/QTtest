#ifndef TOWER_H
#define TOWER_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QPointF>
#include<QObject>
#include<QTimer>

class Tower: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Tower (QGraphicsItem * parent=0);

    QGraphicsPolygonItem * attack_area;

    QPointF attack_dest;
    QPointF AA;

    double distance_to(QGraphicsItem * item);

    void attack_target();
    bool target_exist ;
    QTimer * timer = new QTimer(this);
    QTimer * timerd = new QTimer(this);
    int hp;
    ~Tower();

public slots:
    void dead();
    void acquire_target();


};


#endif // TOWER_H
