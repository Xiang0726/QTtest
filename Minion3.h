#ifndef MINION3_H
#define MINION3_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QTimer>
class Minion3 : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT


public:
    Minion3(QGraphicsItem * parent=0);
    ~Minion3();
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

#endif // MINION3_H
