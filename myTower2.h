#ifndef MYTOWER2_H
#define MYTOWER2_H

#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QPointF>
#include<QObject>
#include<QTimer>

class Tower2: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Tower2 (QGraphicsItem * parent=0);

    QGraphicsPolygonItem * attack_area;

    QPointF attack_dest;
    QPointF AA;

    double distance_to(QGraphicsItem * item);

    void attack_target();
    bool target_exist ;
    int targetexist;
    QTimer * timer ;
    QTimer * timerd ;
    int hp;
    ~Tower2();

public slots:
    void dead();
    void acquire_target();


};


#endif // MYTOWER2_H
