#ifndef FOG_H
#define FOG_H

#include<QObject>
#include<QGraphicsPixmapItem>
#include<QGraphicsItem>
#include<QTimer>

class Fog: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

public:
     Fog();
    ~Fog();
     QTimer * detect_timer = new QTimer(this);
public slots:
     void detect();





};

#endif // FOG_H
