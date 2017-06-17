#include"myTower3.h"
#include<QPixmap>
#include<QVector>
#include<QPointF>
#include<QPolygonF>
#include"Game.h"
#include<QTimer>
#include<QLineF>
#include <QGraphicsRectItem>
#include"Enemy1.h"
#include"Fog.h"
#include"Bullet10.h"
#include<QDebug>

extern Game * game;
Tower3::Tower3(QGraphicsItem *parent): QObject(),  QGraphicsPixmapItem(parent){

    // set graphics
    setPixmap(QPixmap(":/images/maintower.png"));

    // set hp
    hp = 200;

    // craet points vector
    QVector<QPointF> points;
    points << QPointF (1,0) << QPointF (2,0) << QPointF (3,1) << QPointF (3,2) << QPointF (2,3)
           << QPointF (1,3) << QPointF (0,2) << QPointF (0,1);

    // scale
      int scale =65;
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
    QPointF tower_center (x()+70,y()+60);
    QLineF line(polygon_center,tower_center);
    attack_area->setPos(x()+line.dx(),y()+line.dy());

    // connect a timer to attack_target
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(200);

    // connect a timer to dead
    connect(timer,SIGNAL(timeout()),this,SLOT(dead()));
    timerd->start(200);

    // set attack_dest
    attack_dest= QPointF (500,0);
}

double Tower3::distance_to(QGraphicsItem *item){
    QLineF line(pos(),item->pos());
    return line.length();

}

void Tower3::attack_target(){
    if(target_exist == true){
   Bullet1 * bullet = new Bullet1();
   bullet->setPos(x(),y());
   QLineF ln(QPointF(x(),y()),QPointF(attack_dest.x()+30,attack_dest.y()+30));
   int angle = -1 * ln.angle();
   bullet->setRotation(angle);
   game->scene->addItem(bullet);
    }
}

Tower3::~Tower3(){
    // delete timer
    timer->stop();
    delete timer;
    timerd->stop();
    delete timerd;
}

void Tower3::dead(){
    if(this->hp <= 0){
        Game::b+=1;
        scene()->removeItem(this);
        delete this;
        game->final_lose();
        game->warning();
    }
}

void Tower3::acquire_target(){
    // get a list of all items colliding with attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if(colliding_items.size() == 1){
        target_exist = false;
        return;
}
    double closest_dist = 300;
    QPointF closest_point = QPointF (0,0);

    for(size_t a =0,n=colliding_items.size(); a<n; a++)
    {
        Enemy1 * e  = dynamic_cast<Enemy1 *>(colliding_items[a]);
        Bullet10 * b1 = dynamic_cast<Bullet10 *>(colliding_items[a]);
        if(e){
            double this_list =distance_to(e);
              if(this_list < closest_dist){
                 closest_dist = this_list;
                 closest_point = colliding_items[a]->pos();
                 target_exist = true;
            }}

        if(b1){
            this->hp--;
            delete b1;
             }
      }
    attack_dest = closest_point;
    attack_target();
}
