#include"Hero.h"
#include<QPixmap>
#include<QObject>
#include<QTimer>
#include<QGraphicsScene>
#include<QVector>
#include<QPointF>
#include<QPolygonF>
#include<QLineF>
#include "Game.h"
#include <Bullet1.h>
#include <QList>
#include <myTower1.h>
#include "Bullet10.h"
#include"enemyTower1.h"
#include"TBullet1.h"
#include"enemyTower2.h"
#include"enemyTower3.h"
#include <QKeyEvent>


Hero::Hero(QGraphicsPixmapItem *parent)
{
    // draw pic
    setPixmap(QPixmap(":images/EE7.png"));

    connect(life_timer,SIGNAL(timeout()),this,SLOT(dead()));
            life_timer->start(12000);

    connect(attack_timer,SIGNAL(timeout()),this,SLOT(attack()));
    attack_timer->start(50);
}

Hero::~Hero()
{
    life_timer->stop();
    delete life_timer;
}

void Hero::keyPressEvent(QKeyEvent *event)
{
      if (event->key() == Qt::Key_Left){

          setPos(x()-20,y());
      }
      else if (event->key() == Qt::Key_Right){
          setPos(x()+20,y());
      }
      else if (event->key() == Qt::Key_Up){
          setPos(x(),y()-20);
      }
      else if (event->key() == Qt::Key_Down){
          setPos(x(),y()+20);
      }
}

void Hero::attack()
{
    QList<QGraphicsItem *> colliding_items = this-> collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
       if(dynamic_cast<Enemy1*>(colliding_items[i])){
           delete colliding_items[i];
       }
       if(dynamic_cast<fog*>(colliding_items[i])){
           delete colliding_items[i];
       }
    }
}



void Hero::dead()
{
    scene()->removeItem(this);
    delete this;
}
