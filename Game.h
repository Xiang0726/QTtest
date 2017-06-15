#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "Minion1.h"
#include <QKeyEvent>
#include "Minion2.h"
#include "Enemy1.h"
#include<QPushButton>
#include "fog.h"
#include"Fireball.h"
#include"Dialog.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    Game();
    void mousePressEvent(QMouseEvent *event);
    InputDlg myDlg;

    int id;
    void final_win();
    void final_lose();

    // member attributes
    QGraphicsScene * scenewin;        // when wining
    QGraphicsScene * scenelose;       // when losing
    QGraphicsScene * scene_begining;  // for begining
    QGraphicsScene * scene;
    QGraphicsScene * scene_record;    // for record
    QGraphicsScene * scene_rank;      // for rank


    QPushButton * button;
    QPushButton * button1;
    QPushButton * button2;
    QPushButton * button3;
    QPushButton * button4;
    QPushButton * button10;
    QPushButton * button20;
    QPushButton * button30;
    QPushButton * button40;
    QPushButton * hero;
    QPushButton * magic;

    QPushButton * buttonA;
    QPushButton * buttonB;
    QPushButton * buttonC;
    QPushButton *buttonBack;


    static int a;
    static int b;
    int win_1;
    int win_g;

    QTimer * appear_timer= new QTimer(this);
    QTimer * mp          = new QTimer(this);
    QTimer * bad         = new QTimer(this);
    QTimer * energy      = new QTimer(this);
    int r;
    int w;

public slots:

    void chose1();
    void chose2();
    void chose3();
    void chose4();
    void choose1();
    void choose2();
    void choose3();
    void choose4();
    void appear();
    void sethero();
    void mpup();
    void energyup();
    void setmagic();
    void setenemy();

    void beginingA();
    void beginingB();
    void beginingC();
    void back();

};



#endif // GAME_H
