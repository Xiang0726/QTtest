#ifndef MINION4_H
#define MINION4_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QTimer>
class Minion4 : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT


public:
    Minion4(QGraphicsItem * parent=0);
    ~Minion4();
    QGraphicsPolygonItem *attack_area;
    bool has;
    int team;
    void attack();
    QPointF target;
    int hp;
    QTimer * move_timer = new QTimer(this);
    QTimer * hurt_timer = new QTimer(this);

public slots:
    void move();
    void hurt();




};

#endif // MINION4_H
