#include"enemyTower1.h"
#include<QPixmap>
#include<QVector>
#include<QPointF>
#include<QPolygonF>
#include"TBullet1.h"
#include"Game.h"
#include<QTimer>
#include<QLineF>
#include <QGraphicsRectItem>
#include"Minion2.h"
#include"Minion1.h"
#include"Minion3.h"
#include "Bullet3.h"
#include"Fog.h"
#include"Minion4.h"

extern Game * game;
enemyTower1::enemyTower1(QGraphicsItem *parent): QObject(),  QGraphicsPixmapItem(parent){

    // set graphics
    setPixmap(QPixmap(":/images/etower1.png"));

    // set hp
    hp = 200;

    // craet points vector
    QVector<QPointF> points;
    points << QPointF (1,0) << QPointF (2,0) << QPointF (3,1) << QPointF (3,2) << QPointF (2,3)
           << QPointF (1,3) << QPointF (0,2) << QPointF (0,1);

    // scale
      int scale = 70;
      for(size_t a=0,n=points.size();a<n;a++){
          points[a] = points[a] * scale;
      }

    // create a polygon
    QPolygonF polygon(points);

    // creat the QGraphicPolygonItem
    attack_area = new QGraphicsPolygonItem (polygon,this);

    // move the polygon
    QPointF polygon_center(1.5,1.5);
    polygon_center = polygon_center * scale;
    polygon_center = mapToScene(polygon_center);
    QPointF tower_center (x()+55,y()+85);
    QLineF line(polygon_center,tower_center);
    attack_area->setPos(x()+line.dx(),y()+line.dy());

    // connect a timer to attack_target
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(200);

    // connect a timer to dead
    timerd = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(dead()));
    timerd->start(200);

    // set attack_dest
    attack_dest= QPointF (500,0);
}

double enemyTower1::distance_to(QGraphicsItem *item){
    QLineF line(pos(),item->pos());
    return line.length();

}

void enemyTower1::attack_target(){
   if(targetexist == 1){
   TBullet1 * bullet = new TBullet1();
   bullet->setPos(x(),y());
   QLineF ln(QPointF(x(),y()),QPointF(attack_dest.x()+30,attack_dest.y()+30));
   int angle = -1 * ln.angle();
   bullet->setRotation(angle);
   game->scene->addItem(bullet);
   targetexist = 0;
}
}


enemyTower1::~enemyTower1(){
    // delete timer
    timer->stop();
    delete timer;
    timerd->stop();
    delete timerd;
}

void enemyTower1::dead(){
    if(this->hp <= 0){
        Game::a+=1;
        scene()->removeItem(this);
        delete this;
        game->reminding();
        game->final_win();
    }
}

void enemyTower1::acquire_target(){
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if(colliding_items.size() == 1){
        targetexist = 0;
        return;
}
    double closest_dist = 300;
    QPointF closest_point = QPointF (0,0);

    for(size_t a =0,n=colliding_items.size(); a<n; a++)
    {
        Minion2 * m2 = dynamic_cast<Minion2 *>(colliding_items[a]);
        Minion1 * m1 = dynamic_cast<Minion1 *>(colliding_items[a]);
        Minion3 * m3 = dynamic_cast<Minion3 *>(colliding_items[a]);
        Bullet1 * b1 = dynamic_cast<Bullet1 *>(colliding_items[a]);
        Minion4 * m4 = dynamic_cast<Minion4 *>(colliding_items[a]);

        if(m1){
            double this_list =distance_to(m1);
              if(this_list < closest_dist){
                 closest_dist = this_list;
                 closest_point = colliding_items[a]->pos();
                 targetexist = 1;
            }}
   else if(m2){
            double this_list =distance_to(m2);
              if(this_list < closest_dist){
                 closest_dist = this_list;
                 closest_point = colliding_items[a]->pos();
                 targetexist = 1;
            }}
    else if(m4){
                 double this_list =distance_to(m4);
                   if(this_list < closest_dist){
                      closest_dist = this_list;
                      closest_point = colliding_items[a]->pos();
                     targetexist = 1;
                 }}

   else if(m3){
            double this_list =distance_to(m3);
              if(this_list < closest_dist){
                 closest_dist = this_list;
                 closest_point = colliding_items[a]->pos();
                 targetexist = 1;
            }}

  if(b1){
            this->hp--;
            delete b1;
             }


      }
    attack_dest = closest_point;
    attack_target();
}
