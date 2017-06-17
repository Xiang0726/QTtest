#ifndef FIREBALL_H
#define FIREBALL_H
#include<QGraphicsPixmapItem>
#include<QGraphicsItem>
#include<QTimer>
class Fireball : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Fireball(QGraphicsItem * parent = 0);
    ~Fireball();
    QTimer * movetimer;
    QTimer * changetimer;
    QTimer * deadtimer;
    int state;
public slots:
   void move();
   void change();
   void dead();
};
#endif // FIREBALL_H
