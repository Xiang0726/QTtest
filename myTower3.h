#ifndef MYTOWER3_H
#define MYTOWER3_H

#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QPointF>
#include<QObject>
#include<QTimer>

class Tower3: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Tower3 (QGraphicsItem * parent=0);

    QGraphicsPolygonItem * attack_area;

    QPointF attack_dest;
    QPointF AA;

    double distance_to(QGraphicsItem * item);

    void attack_target();
    bool target_exist ;
    int targetexist;
    QTimer * timer = new QTimer(this);
    QTimer * timerd = new QTimer(this);
    int hp;
    ~Tower3();

public slots:
    void dead();
    void acquire_target();


};


#endif // MYTOWER3_H
