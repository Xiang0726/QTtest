#include"Enemy1.h"
#include<QPixmap>
#include<QObject>
#include<QTimer>
#include<QGraphicsScene>
#include<QVector>
#include<QPointF>
#include<QPolygonF>
#include<QLineF>
#include "Game.h"
#include"Bullet1.h"
#include"Minion1.h"
#include"Bullet10.h"
#include"Bullet3.h"
#include"Minion3.h"
#include"myTower1.h"
#include"myTower2.h"
#include"myTower3.h"
#include"Minion4.h"

extern Game * game;

Enemy1::Enemy1(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    // define hp
    hp = 10;

    // draw pic
    setPixmap(QPixmap(":images/Minion.png"));

    // set timer
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(200);

    // create a polygon
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
           << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);
    // scale polygon
    int i,n;
    int scale = 60;
    for(i=0,n=points.size();i<n;i++){
       points[i]=points[i]*scale;
   }

    // create polygonitem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);

    // match polygon and minion
    QPointF poly_center(1.5,1.5);
    poly_center = poly_center * scale;
    poly_center = mapToScene(poly_center);
    QPointF Minion_center(x()+28,y()+40);
    QLineF ln(poly_center,Minion_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());
}

void Enemy1::hpdecreace()
{
    hp--;
}

void Enemy1::attack()
{
    QLineF lnn(this -> pos(),QPointF(target.x()+30,target.y()+30));
    int angle = -1 * lnn.angle();
    Bullet10 *bullet10 = new Bullet10;
    bullet10 ->from = 10;
    bullet10 -> setPos(x(),y());
    bullet10 ->setRotation(angle);
    game -> scene -> addItem(bullet10);
}

Enemy1::~Enemy1(){
    // delete timer
    move_timer->stop();
    delete move_timer;
}

void Enemy1::move(){
     int closedistance=200;
     setPos(x()-5,y());
     has = false;
     QList<QGraphicsItem *> colliding_items = attack_area -> collidingItems();
     for (int i = 0, n = colliding_items.size(); i < n; ++i)
     {

         if( dynamic_cast<Minion1*>(colliding_items[i])
           ||dynamic_cast<Minion2*>(colliding_items[i])
           ||dynamic_cast<Minion3*>(colliding_items[i])
           ||dynamic_cast<Minion4*>(colliding_items[i]))
           {

         QLineF ln(this->pos(),colliding_items[i]->pos());
         int distance = ln.length();

             if(distance<=closedistance){
                 closedistance = distance;
                 target = colliding_items[i]->pos();
                 has = true;
               }
            }
         if(dynamic_cast<Tower1*>  (colliding_items[i])){

             QLineF ln(this->pos(),colliding_items[i]->pos());
             int distance = ln.length();

                 if(distance<=closedistance){
                     closedistance = distance;
                     target = colliding_items[i]->pos();
                     has = true;
                     setPos(x()+5,y());
                   }
                }
         if(dynamic_cast<Tower2*>  (colliding_items[i])){

             QLineF ln(this->pos(),colliding_items[i]->pos());
             int distance = ln.length();

                 if(distance<=closedistance){
                     closedistance = distance;
                     target = colliding_items[i]->pos();
                     has = true;
                     setPos(x()+5,y());
                   }
                }
         if(dynamic_cast<Tower3*>  (colliding_items[i])){

             QLineF ln(this->pos(),colliding_items[i]->pos());
             int distance = ln.length();

                 if(distance<=closedistance){
                     closedistance = distance;
                     target = colliding_items[i]->pos();
                     has = true;
                     setPos(x()+5,y());
                   }
                }


         else if(dynamic_cast<Enemy1*>(colliding_items[i])==this){ continue; }

         if(dynamic_cast<Bullet1*>(colliding_items[i])){
                hp--;
             delete colliding_items[i];
         }
     }

     if(has == true){
        attack();

       if(this->hp <= 0){
         scene() ->removeItem(this);
         delete this;
                        }
                    }

     if (pos().x()>1300){
             scene()->removeItem(this);
             delete this;
                        }
}


