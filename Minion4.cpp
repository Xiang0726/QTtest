#include"Minion4.h"
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
#include <Tower.h>
#include "Bullet10.h"
#include"Bullet3.h"
#include"enemyTower1.h"
#include"TBullet1.h"
#include"enemyTower2.h"
#include"enemyTower3.h"
extern Game * game;

Minion4::Minion4(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // define HP
    hp = 30;

    // draw pic
    setPixmap(QPixmap(":images/EE5.png"));

    // set timer
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(200);

    // set timer for hurt
    connect(hurt_timer,SIGNAL(timeout()),this,SLOT(hurt()));
    hurt_timer->start(100);

    // create a polygon
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
           << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale polygon
    int i,n;
    int scale = 40;
    for(i=0,n=points.size();i<n;i++){
       points[i]=points[i]*scale;
   }

    // create polygonitem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);

    // match polygon and minion
    QPointF poly_center(1.5,1.5);
    poly_center = poly_center * scale;
    poly_center = mapToScene(poly_center);
    QPointF Minion_center(x()+40,y()+45);
    QLineF ln(poly_center,Minion_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());
}

Minion4::~Minion4(){
    // delete timer
    move_timer->stop();
    delete move_timer;
    hurt_timer->stop();
    delete hurt_timer;
}

void Minion4::attack()
{
    QLineF lnn(this -> pos(),QPointF(target.x()+30,target.y()+30));
    int angle = -1 * lnn.angle();
    Bullet1 *bullet1 = new Bullet1;
    bullet1 -> setPos(x(),y());
    bullet1 ->setRotation(angle);
    game -> scene -> addItem(bullet1);
}

void Minion4::move(){
     int closedistance=200;
     setPos(x()+10,y());
     has = false;
     QList<QGraphicsItem *> colliding_items = attack_area -> collidingItems();
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if(dynamic_cast<enemyTower1*>(colliding_items[i])){
             QLineF ln(this->pos(),colliding_items[i]->pos());
             int distance = ln.length();

                 if(distance<=closedistance){
                     closedistance = distance;
                     target = colliding_items[i]->pos();
                     has = true;
                     setPos(x()-10,y());
         }}



         else if(dynamic_cast<enemyTower2*>(colliding_items[i])){
             QLineF ln(this->pos(),colliding_items[i]->pos());
             int distance = ln.length();

                 if(distance<=closedistance){
                     closedistance = distance;
                     target = colliding_items[i]->pos();
                     has = true;
                     setPos(x()-10,y());
         }}

         else if( dynamic_cast<Enemy1*>(colliding_items[i])){
         QLineF ln(this->pos(),colliding_items[i]->pos());
         int distance = ln.length();

             if(distance<=closedistance){
                 closedistance = distance;
                 target = colliding_items[i]->pos();
                 has = true;
               }
            }
         else if(dynamic_cast<enemyTower3*>(colliding_items[i])){
             QLineF ln(this->pos(),colliding_items[i]->pos());
             int distance = ln.length();

                 if(distance<=closedistance){
                     closedistance = distance;
                     target = colliding_items[i]->pos();
                     has = true;
                     setPos(x()-10,y());
         }}


         else if(dynamic_cast<Bullet10*>(colliding_items[i])){
                      this->hp--;
                 }
         if(dynamic_cast<fog*>(colliding_items[i])){

             delete colliding_items[i];
         }
         if(dynamic_cast<TBullet1*>(colliding_items[i])){

             delete colliding_items[i];
         }
           }

     if(has == true){
        attack();
                    }

     if(this->hp <= 0){
         scene() ->removeItem(this);
         delete this;
                      }

     if (pos().x()>1300){
             scene()->removeItem(this);
             delete this;
     }
}

void Minion4::hurt(){
    QList<QGraphicsItem *> colliding_items = attack_area -> collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(dynamic_cast<TBullet1*>(colliding_items[i])){ this->hp--; }
        else if(dynamic_cast<Bullet10*>(colliding_items[i])){ this->hp--; }
    }
}
