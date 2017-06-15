#ifndef HERO_H
#define HERO_H
#include<QGraphicsPixmapItem>
#include<QGraphicsPolygonItem>
#include<QGraphicsItem>
#include<QTimer>
#include<QPixmap>
#include<QObject>

class Hero:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Hero(QGraphicsPixmapItem * parent = 0);
    ~Hero();
    void keyPressEvent(QKeyEvent * event);
    QTimer * life_timer = new QTimer(this);
    QTimer * attack_timer= new QTimer(this);
public slots:
    void attack();
    void dead();
};

#endif // HERO_H
