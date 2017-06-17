#ifndef MINION2_H
#define MINION2_H

#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QTimer>
class Minion2 : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Minion2(QGraphicsItem * parent=0);
    ~Minion2();
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
#endif // MINION2_H

