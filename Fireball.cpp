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
{   state = 1;
    // draw

    changetimer = new QTimer(this);
    connect(changetimer,SIGNAL(timeout()),this,SLOT(change()));
    changetimer ->start(500);


    movetimer = new QTimer(this);
    connect(movetimer,SIGNAL(timeout()),this,SLOT(move()));
    movetimer -> start(50);



    deadtimer = new QTimer(this);
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

void Fireball::change()
{ if(state == 1){
          setPixmap(QPixmap(":images/fires.png"));
          state = 2;

            }
 else if(state ==2){
          setPixmap(QPixmap(":images/fire.png"));
          state = 1;
    }

}




void Fireball::dead()
{
   scene() ->removeItem(this);
   delete this;
}
