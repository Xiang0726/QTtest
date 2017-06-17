#include"Minion1.h"
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
#include"fog.h"
extern Game * game;

Minion1::Minion1(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // define HP
    hp = 10;

    // draw pic
    setPixmap(QPixmap(":images/EE1.png"));

    // set timer for move
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
    QPointF Minion_center(x()+30,y()+50);
    QLineF ln(poly_center,Minion_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());
}

Minion1::~Minion1(){
    // delete timer
    move_timer->stop();
    delete move_timer;
    hurt_timer->stop();
    delete hurt_timer;
}

void Minion1::attack(){
    QLineF lnn(this -> pos(),QPointF(target.x()+30,target.y()+30));
    int angle = -1 * lnn.angle();
    Bullet1 *bullet1 = new Bullet1;
    bullet1 -> setPos(x(),y());
    bullet1 ->setRotation(angle);
    game -> scene -> addItem(bullet1);
}

void Minion1::move(){
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
         else if(dynamic_cast<enemyTower3*>(colliding_items[i])){
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
         else if(dynamic_cast<Minion1*>(colliding_items[i])==this){ continue;}
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

void Minion1::hurt(){
    QList<QGraphicsItem *> colliding_items = attack_area -> collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {   Bullet10 * b1 = dynamic_cast<Bullet10 *>(colliding_items[i]);
        TBullet1 * b2 = dynamic_cast<TBullet1 *>(colliding_items[i]);
        if(b1){ this->hp--;
                scene()->removeItem(b1);
                delete b1;
        }
        if(b2){ this ->hp--;
                scene()->removeItem(b2);
                delete b2;
        }
}
}
