#include<QTimer>
#include"Game.h"
#include"Minion1.h"
#include"Minion2.h"
#include"Minion3.h"
#include"Minion4.h"
#include"Enemy1.h"
#include<QPixmap>
#include<QObject>
#include"Fireball.h"
#include<QList>
extern Game * game;

Fireball::Fireball(QGraphicsItem *parent)
{
    // draw pic
    setPixmap(QPixmap(":images/fire.png"));

    connect(movetimer,SIGNAL(timeout()),this,SLOT(move()));
    movetimer -> start(50);

   connect(deadtimer,SIGNAL(timeout()),this,SLOT(dead()));
   deadtimer -> start(50000);
}

Fireball::~Fireball()
{
    movetimer->stop();
    deadtimer->stop();
    delete movetimer;
    delete deadtimer;
}

void Fireball::move()
{
    setPos(x(),y()+5);
    QList<QGraphicsItem *> colliding_items = this -> collidingItems();
    int a = colliding_items.size();
    for(int i =0;i<a;i++){
         if(dynamic_cast<fog*>(colliding_items[i])){
             delete colliding_items[i];
         }
         if(dynamic_cast<Enemy1*>(colliding_items[i])){
             delete colliding_items[i];
         }
    }

}

void Fireball::dead()
{
   scene() ->removeItem(this);
   delete this;
}
