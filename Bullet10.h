#ifndef BULLET10_H
#define BULLET10_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include<QTimer>
class Bullet10: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet10(QGraphicsItem * parent=0);
    QTimer * move_timer = new QTimer(this);
    ~Bullet10();
    int from;

public slots:
    void move();
};
#endif // BULLET10_H
