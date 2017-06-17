#ifndef MINION1_H
#define MINION1_H

#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QTimer>
class Minion1 : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT


public:
    Minion1(QGraphicsItem * parent=0);
    ~Minion1();
    QGraphicsPolygonItem *attack_area;
    bool has;
    int team;
    void attack();
    QPointF target;

    int hp;
    QTimer * move_timer ;
    QTimer * hurt_timer ;
public slots:
    void move();
    void hurt();



};

#endif // MINION1_H
