#include <QPixmap>
#include <QTimer>
#include <qmath.h> // qSin, qCos, qTan
#include "Game.h"
#include <QLine>
#include <QList>
#include "Enemy1.h"
#include"Bullet3.h"
#include"enemyTower1.h"
#include"enemyTower2.h"
#include"enemyTower3.h"
extern Game * game;

Bullet3::Bullet3(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent){

    // set graphics
    setPixmap(QPixmap(":images/bullet.jpg"));

    // connect a timer to move()
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(10);
}

Bullet3::~Bullet3(){
    // delete timer
    move_timer->stop();
    delete move_timer;
}

void Bullet3::move(){
    double slope = 4;
    double theta = rotation();
    double dy = slope * qSin(qDegreesToRadians(theta));
    double dx = slope * qCos(qDegreesToRadians(theta));
    this ->setPos(x()+dx,y()+dy);

    //delete after collide with enemy
    QList <QGraphicsItem*>coenemy = this -> collidingItems();
    int a = coenemy.size();
    for(int i = 0;i<a;i++){
        if(typeid(*(coenemy[i])) == typeid(Enemy1)||this->x()>2000||this->x()<-500||typeid(*(coenemy[i])) == typeid(enemyTower1)
                ||typeid(*(coenemy[i])) == typeid(enemyTower2)||typeid(*(coenemy[i])) == typeid(enemyTower3)){

              scene() -> removeItem(this);
              delete this;
              break;
          }
      }
}
