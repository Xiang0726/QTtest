#include <QPixmap>
#include <QTimer>
#include <qmath.h> // qSin, qCos, qTan
#include "Game.h"
#include <QLine>
#include <QList>
#include "Enemy1.h"
#include "enemyTower1.h"
#include "enemyTower2.h"
#include "enemyTower3.h"

extern Game * game;

Bullet1::Bullet1(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent){

    // set graphics
    setPixmap(QPixmap(":images/bullet1.png"));

    // connect a timer to move()
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(10);
}

Bullet1::~Bullet1(){
    // delete timer
    move_timer->stop();
    delete move_timer;
}

void Bullet1::move(){
    double slope =4;
    double theta = rotation();
    double dy = slope * qSin(qDegreesToRadians(theta));
    double dx = slope * qCos(qDegreesToRadians(theta));
    this ->setPos(x()+dx,y()+dy);

    if(this->x()>1000){
        scene()->removeItem(this);
        delete this;
    }


 }
