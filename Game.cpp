#include"Game.h"
#include"Minion1.h"
#include"Minion2.h"
#include <QGraphicsScene>
#include <QLabel>
#include <Enemy1.h>
#include <Bullet1.h>
#include"myTower1.h"
#include"myTower2.h"
#include"myTower3.h"
#include"enemyTower1.h"
#include"Minion3.h"
#include"enemyTower2.h"
#include"enemyTower3.h"
#include<QLabel>
#include<QTime>
#include<stdlib.h>
#include"Fog.h"
#include"Minion4.h"
#include"Hero.h"
#include"Fireball.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QVector>
#include"Dialog.h"
#include<QDebug>


int Game::a = 0;
int Game::b = 0;
extern Game * game;

Game::Game(){
    myDlg.show();

    // create a scene after sign in
    scene_begining = new QGraphicsScene();
    scene_begining->setSceneRect(0,0,400,300);
    setScene(scene_begining);

    // create two buttons
    buttonA = new QPushButton("開始遊戲");
    buttonB = new QPushButton("查看帳號紀錄");
    buttonC = new QPushButton("查看排名");

    // add two buttons to scene_begining
    scene_begining->addWidget(buttonA);
    buttonA->setGeometry(200,200,100,100);
    scene_begining->addWidget(buttonB);
    buttonB->setGeometry(0,200,100,100);
    scene_begining->addWidget(buttonC);
    buttonC->setGeometry(100,200,100,100);

    // connect two button to scene_begining
    connect(buttonA,SIGNAL(clicked()),this,SLOT(beginingA())); // for play
    connect(buttonB,SIGNAL(clicked()),this,SLOT(beginingB())); // for record
    connect(buttonC,SIGNAL(clicked()),this,SLOT(beginingC())); // for rank

    qsrand(time(NULL));
}

void Game::final_win()
{
    if(a==3){
                reminding_timer->stop();
                // clear scene and reset a new scene
                scene->clear();
                scenewin = new QGraphicsScene();
                scenewin->setSceneRect(0,0,800,600);
                setScene(scenewin);

                // display win

                QLabel * win = new QLabel();
                win->setText("你贏得這場遊戲");
                win->setAlignment(Qt::AlignCenter);
                win->setGeometry(200,200,200,50);
                scenewin->addWidget(win);

                // create a button back to scene_begining
                buttonBack = new QPushButton("返回主畫面");
                buttonBack->setGeometry(300,0,100,100);
                scenewin->addWidget(buttonBack);
                connect(buttonBack,SIGNAL(clicked()),this,SLOT(back()));

                a= 0; // set a=0

                if(myDlg.c+myDlg.ccc==2) // when the account is gsn
              {
                // get the number of "gsn_win"
                QFile file_win("/home/pd2vm/QTtest/gsn_win.txt");
                file_win.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text );
                QTextStream win_in(&file_win);
                win_in >> win_g;
                ++win_g;
                file_win.close();


                // rewrite the number of "gsn_win"
                file_win.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text|QIODevice::Truncate );
                win_in << win_g;
                file_win.close();

                // rewrite the data in my account
                QFile file("/home/pd2vm/QTtest/data.txt");
                file.open(QIODevice::ReadOnly| QIODevice::WriteOnly| QIODevice::Text |QIODevice::Truncate );
                QTextStream in(&file);
                in << QObject::tr("你的帳號") << endl;
                in << QObject::tr("帳號:") << myDlg.a << endl;
                in << QObject::tr("密碼:") << myDlg.b << endl;
                in << QObject::tr("勝場數:") << win_g << endl;
                file.close();
                }

                if(myDlg.cc+myDlg.cccc==2) // when the account is 123
              {
                // get the number of "123_win"
                QFile file_win("/home/pd2vm/QTtest/123_win.txt");
                file_win.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text );
                QTextStream win_in(&file_win);
                win_in >> win_1;
                ++win_1;
                file_win.close();

                // rewrite the number of "123_win"
                file_win.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text|QIODevice::Truncate );
                win_in << win_1;

                // rewrite the data in my account
                QFile file("/home/pd2vm/QTtest/data_123.txt");
                file.open(QIODevice::ReadOnly| QIODevice::WriteOnly| QIODevice::Text |QIODevice::Truncate );
                QTextStream in(&file);
                in << QObject::tr("你的帳號") << endl;
                in << QObject::tr("帳號:") << myDlg.aa << endl;
                in << QObject::tr("密碼:") << myDlg.bb << endl;
                in << QObject::tr("勝場數:") << win_1 << endl;
                file.close();
              }

             }
    }

void Game::final_lose()
{
    if(b==3){
    warning_timer->stop();
    scene->clear();
    scenelose = new QGraphicsScene();
    scenelose->setSceneRect(0,0,800,600);
    setScene(scenelose);

    // display lose
    QLabel * lose = new QLabel();
    lose->setText("你輸了這場遊戲");
    lose->setAlignment(Qt::AlignCenter);
    lose->setAlignment(Qt::AlignCenter);
    lose->setGeometry(200,200,200,50);
    scenelose->addWidget(lose);

    // create a button back to scene_begining
    buttonBack = new QPushButton("返回主畫面");
    buttonBack->setGeometry(300,0,100,100);
    scenelose->addWidget(buttonBack);
    connect(buttonBack,SIGNAL(clicked()),this,SLOT(back()));
    // stop the warning_timer or it will crash the fuck down

    b=0;
            }
}

void Game::warning()
{
    if(b==2)
    {
        warning1 = new QLabel();
        warning1->setText(tr("你快要G了"));
        warning1->setAlignment(Qt::AlignCenter);
        warning1->setGeometry(-200,300,80,30);
        scene->addWidget(warning1);

        // create a timer for sending warning
        warning_timer = new QTimer(warning1);
        connect(warning_timer,SIGNAL(timeout()),this,SLOT(sending_warning()));
        warning_timer->start(1000);
    }
}

void Game::sending_warning()
{
    warning1->setVisible(! warning1->isVisible());
    qDebug() << "A";
}


void Game::reminding()
{
    if(a==2)
    {
        reminding1 = new QLabel();
        reminding1->setText(tr("你快要贏了"));
        reminding1->setAlignment(Qt::AlignCenter);
        reminding1->setGeometry(-200,350,80,30);
        scene->addWidget(reminding1);

        // create a timer for sending warning
        reminding_timer = new QTimer(reminding1);
        connect(reminding_timer,SIGNAL(timeout()),this,SLOT(sending_reminding()));
        reminding_timer->start(1000);
    }
}

void Game::sending_reminding()
{
    reminding1->setVisible(!reminding1->isVisible());
}

void Game::beginingA(){

    // create scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
    bg = new QGraphicsPixmapItem;
    bg ->setPixmap(QPixmap(":images/bg3.jpg"));
    scene->addItem(bg);
    bg->setPos(-300,0);


    // create tower
    Tower1 * t1 = new Tower1();
    t1->setPos(50,40);
    Tower2 * t2 = new Tower2();
    t2->setPos(0,240);
    Tower3 * t3 = new Tower3();
    t3->setPos(50,440);

    enemyTower1 * t10 = new enemyTower1();
    t10->setPos(800,40);
    enemyTower2 * t20 = new enemyTower2();
    t20->setPos(850,240);
    enemyTower3 * t30 = new enemyTower3();
    t30->setPos(800,440);

    // add tower to scene
    scene->addItem(t10);
    scene->addItem(t20);
    scene->addItem(t30);
    scene->addItem(t1);
    scene->addItem(t2);
    scene->addItem(t3);

    button1 = new QPushButton("斯國峰");
    button1 ->setGeometry(-200,100,100,100);
    scene->addWidget(button1);
    connect(button1, SIGNAL(clicked()), this, SLOT(chose1()));

    button10 = new QPushButton("斯國峰");
    button10 ->setGeometry(-200,200,100,100);
    scene->addWidget(button10);
    connect(button10, SIGNAL(clicked()), this, SLOT(choose1()));

    hero = new QPushButton("hero");
    hero ->setGeometry(-200,400,50,50);
    scene ->addWidget(hero);
    connect(hero,SIGNAL(clicked()),this,SLOT(sethero()));

    connect(appear_timer,SIGNAL(timeout()),this,SLOT(appear()));
    appear_timer->start(0.0000000001);

    magic = new QPushButton("magic");
    magic ->setGeometry(-200,500,50,50);
    scene ->addWidget(magic);
    connect(magic,SIGNAL(clicked()),this,SLOT(setmagic()));

    connect(mp,SIGNAL(timeout()),this,SLOT(mpup()));
    mp -> start(3000);

    connect(bad,SIGNAL(timeout()),this,SLOT(setenemy()));
    bad ->start(4000);

    connect(energy,SIGNAL(timeout()),this,SLOT(energyup()));
    energy->start(25000);
}

void Game::beginingB(){
    // show the recond which is dated back to last game
    scene_record = new QGraphicsScene(0,0,300,400);
    setScene(scene_record);
    // create a button back to scene_begining
    buttonBack = new QPushButton("返回主畫面");
    buttonBack->setGeometry(300,0,100,100);
    scene_record->addWidget(buttonBack);
    connect(buttonBack,SIGNAL(clicked()),this,SLOT(back()));

    if(myDlg.c+myDlg.ccc==2)
    {
       QFile file("/home/pd2vm/QTtest/data.txt");
       file.open(QIODevice::ReadOnly| QIODevice::WriteOnly| QIODevice::Text );
       QTextStream out(&file);

       QVector<QString>text(4);
              for(int a=0;a<4;a++)
              {
                out>>text[a]>>endl;
                QLabel * label = new QLabel(text.at(a));
                label->setGeometry(0,a*100,150,50);
                scene_record->addWidget(label);
              }
       file.close();
         }

     if(myDlg.cc==1&&myDlg.cccc==1)
     {
         QFile file("/home/pd2vm/QTtest/data_123.txt");
         file.open(QIODevice::ReadOnly| QIODevice::WriteOnly| QIODevice::Text );
         QTextStream out(&file);

         QVector<QString>text(4);
                for(int a=0;a<4;a++)
               {
                 out>>text[a]>>endl;
                 QLabel * label = new QLabel(text.at(a));
                 label->setGeometry(0,a*100,150,50);
                 scene_record->addWidget(label);
               }
         file.close();
      }
}

void Game::beginingC()
{
    // create scene_rank
    scene_rank = new QGraphicsScene();
    scene_rank->setSceneRect(0,0,800,600);
    setScene(scene_rank);

    // get the number of win_gsn_now
    QFile file_gsn("/home/pd2vm/QTtest/gsn_win.txt");
    file_gsn.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream gsn_in(&file_gsn);
    int win_gsn_now;
    gsn_in >> win_gsn_now;
    file_gsn.close();

    // get the number of win_a123_now
    QFile file_a123("/home/pd2vm/QTtest/123_win.txt");
    file_a123.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream a123_in(&file_a123);
    int win_a123_now;
    a123_in >> win_a123_now;
    file_a123.close();

    // rewrite the data in rank after playing
    QFile file_rank("/home/pd2vm/QTtest/rank.txt");
    file_rank.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
    QTextStream rankin(&file_rank);
    rankin << QObject::tr("遊戲排名") << endl;

    if(win_a123_now > win_gsn_now)
    {
        rankin << QObject::tr("第一名:") << myDlg.aa << QObject::tr("  勝場數:") << win_a123_now << endl;
        rankin << QObject::tr("第二名:") << myDlg.a << QObject::tr("   勝場數:") << win_gsn_now << endl;
    }

    else if(win_a123_now < win_gsn_now)
    {
        rankin << QObject::tr("第一名:") << myDlg.a << QObject::tr("   勝場數:") << win_gsn_now << endl;
        rankin << QObject::tr("第二名:") << myDlg.aa << QObject::tr("   勝場數:") << win_a123_now << endl;
    }
    else if(win_a123_now == win_gsn_now)
    {
        rankin << QObject::tr("第一名:") << myDlg.a << QObject::tr("   勝場數:") << win_gsn_now << endl;
        rankin << QObject::tr("第一名:") << myDlg.aa << QObject::tr("   勝場數:") << win_a123_now << endl;
    }
    file_rank.close();

    // show the data to scene_rank
    QFile file_rankout("/home/pd2vm/QTtest/rank.txt");
    file_rankout.open(QIODevice::ReadOnly | QIODevice::Text );
    QTextStream rankout(&file_rankout);
    QVector<QString>text(5);
           for(int a=0;a<5;a++)
          {
            rankout >> text[a]  ;
            QLabel * label = new QLabel(text.at(a));
            label->setGeometry(0,a*100,150,50);
            scene_rank->addWidget(label);
          }
    file_rank.close();

    // create a button back to scene_begining
    buttonBack = new QPushButton("返回主畫面");
    buttonBack->setGeometry(300,0,100,100);
    scene_rank->addWidget(buttonBack);
    connect(buttonBack,SIGNAL(clicked()),this,SLOT(back()));
}


void Game::chose1()
{
    id = 1;
    int aa = qrand()%4+1;
    //delete button1;
    if(aa==1){
        button1 = new QPushButton("斯國峰");
        button1 ->setGeometry(-200,100,100,100);
        scene->addWidget(button1);
        connect(button1, SIGNAL(clicked()), this, SLOT(chose1()));
       }
    if(aa==2){
        button2 = new QPushButton("張名先");
        button2 ->setGeometry(-200,100,100,100);
        scene->addWidget(button2);
        connect(button2, SIGNAL(clicked()), this, SLOT(chose2()));
       }
    if(aa==3){
        button3 = new QPushButton("李國君");
        button3 ->setGeometry(-200,100,100,100);
        scene->addWidget(button3);
        connect(button3, SIGNAL(clicked()), this, SLOT(chose3()));
       }
    if(aa==4){
        button4 = new QPushButton("王醴");
        button4 ->setGeometry(-200,100,100,100);
        scene->addWidget(button4);
        connect(button4, SIGNAL(clicked()), this, SLOT(chose4()));
    }
}

void Game::chose2()
{
    id = 2;
    int aa = qrand()%4+1;
    //delete button2;
    if(aa==1){
        button1 = new QPushButton("斯國峰");
        button1 ->setGeometry(-200,100,100,100);
        scene->addWidget(button1);
        connect(button1, SIGNAL(clicked()), this, SLOT(chose1()));
       }
    if(aa==2){
        button2 = new QPushButton("張名先");
        button2 ->setGeometry(-200,100,100,100);
        scene->addWidget(button2);
        connect(button2, SIGNAL(clicked()), this, SLOT(chose2()));
       }
    if(aa==3){
        button3 = new QPushButton("李國君");
        button3 ->setGeometry(-200,100,100,100);
        scene->addWidget(button3);
        connect(button3, SIGNAL(clicked()), this, SLOT(chose3()));
       }
    if(aa==4){
        button4 = new QPushButton("王醴");
        button4 ->setGeometry(-200,100,100,100);
        scene->addWidget(button4);
        connect(button4, SIGNAL(clicked()), this, SLOT(chose4()));
    }
}

void Game::chose3()
{
    id = 3;
    int aa = qrand()%4+1;
    //delete button3;
    if(aa==1){
        button1 = new QPushButton("斯國峰");
        button1 ->setGeometry(-200,100,100,100);
        scene->addWidget(button1);
        connect(button1, SIGNAL(clicked()), this, SLOT(chose1()));
       }
    if(aa==2){
        button2 = new QPushButton("張名先");
        button2 ->setGeometry(-200,100,100,100);
        scene->addWidget(button2);
        connect(button2, SIGNAL(clicked()), this, SLOT(chose2()));
       }
    if(aa==3){
        button3 = new QPushButton("李國君");
        button3 ->setGeometry(-200,100,100,100);
        scene->addWidget(button3);
        connect(button3, SIGNAL(clicked()), this, SLOT(chose3()));
       }
    if(aa==4){
        button4 = new QPushButton("王醴");
        button4 ->setGeometry(-200,100,100,100);
        scene->addWidget(button4);
        connect(button4, SIGNAL(clicked()), this, SLOT(chose4()));
    }
}

void Game::chose4()
{
    id = 4;
    int aa = qrand()%4+1;
    //delete button4;
    if(aa==1){
        button1 = new QPushButton("斯國峰");
        button1 ->setGeometry(-200,100,100,100);
        scene->addWidget(button1);
        connect(button1, SIGNAL(clicked()), this, SLOT(chose1()));
       }
    if(aa==2){
        button2 = new QPushButton("張名先");
        button2 ->setGeometry(-200,100,100,100);
        scene->addWidget(button2);
        connect(button2, SIGNAL(clicked()), this, SLOT(chose2()));
       }
    if(aa==3){
        button3 = new QPushButton("李國君");
        button3 ->setGeometry(-200,100,100,100);
        scene->addWidget(button3);
        connect(button3, SIGNAL(clicked()), this, SLOT(chose3()));
       }
    if(aa==4){
        button4 = new QPushButton("王醴");
        button4 ->setGeometry(-200,100,100,100);
        scene->addWidget(button4);
        connect(button4, SIGNAL(clicked()), this, SLOT(chose4()));
    }
}

void Game::choose1()
{
    id = 1;
    int bb = qrand()%4+1;
    //delete button1;
    if(bb==1){
        button10 = new QPushButton("斯國峰");
        button10->setGeometry(-200,200,100,100);
        scene->addWidget(button10);
        connect(button10, SIGNAL(clicked()), this, SLOT(choose1()));
       }
    if(bb==2){
        button20 = new QPushButton("張名先");
        button20 ->setGeometry(-200,200,100,100);
        scene->addWidget(button20);
        connect(button20, SIGNAL(clicked()), this, SLOT(choose2()));
       }
    if(bb==3){
        button30 = new QPushButton("李國君");
        button30 ->setGeometry(-200,200,100,100);
        scene->addWidget(button30);
        connect(button30, SIGNAL(clicked()), this, SLOT(choose3()));
       }
    if(bb==4){
        button40 = new QPushButton("王醴");
        button40 ->setGeometry(-200,200,100,100);
        scene->addWidget(button40);
        connect(button40, SIGNAL(clicked()), this, SLOT(choose4()));
    }
}

void Game::choose2()
{
    id = 2;
    int bb = qrand()%4+1;
    //delete button2;
    if(bb==1){
        button10 = new QPushButton("斯國峰");
        button10 ->setGeometry(-200,200,100,100);
        scene->addWidget(button10);
        connect(button10, SIGNAL(clicked()), this, SLOT(choose1()));
       }
    if(bb==2){
        button20 = new QPushButton("張名先");
        button20 ->setGeometry(-200,200,100,100);
        scene->addWidget(button20);
        connect(button20, SIGNAL(clicked()), this, SLOT(choose2()));
       }
    if(bb==3){
        button30 = new QPushButton("李國君");
        button30 ->setGeometry(-200,200,100,100);
        scene->addWidget(button30);
        connect(button30, SIGNAL(clicked()), this, SLOT(choose3()));
       }
    if(bb==4){
        button40 = new QPushButton("王醴");
        button40 ->setGeometry(-200,200,100,100);
        scene->addWidget(button40);
        connect(button40, SIGNAL(clicked()), this, SLOT(choose4()));
    }
}

void Game::choose3()
{
    id = 3;
    int bb = qrand()%4+1;
    //delete button3;
    if(bb==1){
        button10 = new QPushButton("斯國峰");
        button10 ->setGeometry(-200,200,100,100);
        scene->addWidget(button10);
        connect(button10, SIGNAL(clicked()), this, SLOT(choose1()));
       }
    if(bb==2){
        button20 = new QPushButton("張名先");
        button20 ->setGeometry(-200,200,100,100);
        scene->addWidget(button20);
        connect(button20, SIGNAL(clicked()), this, SLOT(choose2()));
       }
    if(bb==3){
        button30 = new QPushButton("李國君");
        button30 ->setGeometry(-200,200,100,100);
        scene->addWidget(button30);
        connect(button30, SIGNAL(clicked()), this, SLOT(choose3()));
       }
    if(bb==4){
        button40 = new QPushButton("王醴");
        button40 ->setGeometry(-200,200,100,100);
        scene->addWidget(button40);
        connect(button40, SIGNAL(clicked()), this, SLOT(choose4()));
    }
}

void Game::choose4()
{
    id = 4;
    int bb = qrand()%4+1;
    //delete button4;
    if(bb==1){
        button10 = new QPushButton("斯國峰");
        button10 ->setGeometry(-200,200,100,100);
        scene->addWidget(button10);
        connect(button10, SIGNAL(clicked()), this, SLOT(choose1()));
       }
    if(bb==2){
        button20 = new QPushButton("張名先");
        button20 ->setGeometry(-200,200,100,100);
        scene->addWidget(button20);
        connect(button20, SIGNAL(clicked()), this, SLOT(choose2()));
       }
    if(bb==3){
        button30 = new QPushButton("李國君");
        button30 ->setGeometry(-200,200,100,100);
        scene->addWidget(button30);
        connect(button30, SIGNAL(clicked()), this, SLOT(choose3()));
       }
    if(bb==4){
        button40 = new QPushButton("王醴");
        button40 ->setGeometry(-200,200,100,100);
        scene->addWidget(button40);
        connect(button40, SIGNAL(clicked()), this, SLOT(choose4()));
    }
}

void Game::appear(){
    int x1 = qrand()%350+400;
    int y1 = qrand()%600;
    int x2 = qrand()%350+400;
    int y2 = qrand()%600;
    fog * f1 = new fog();
    fog * f2 = new fog();
    f1 ->setPos(x1,y1);
    scene ->addItem(f1);
    f2 ->setPos(x2,y2);
    scene ->addItem(f2);
}

void Game::sethero()
{if(r==1){
    Hero * hero = new Hero();
    hero ->setPos(100,400);
    scene->addItem(hero);
    hero ->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    hero ->setFocus();
}
    r =2;
}

void Game::mpup()
{
    w = 1;
}

void Game::energyup()
{
    r = 1;
}

void Game::setmagic()
{
    if(w==1){
        int a = qrand()%400+200;
        Fireball * b = new Fireball();
        b ->setPos(a,0);
        scene->addItem(b);
    }
    w = 2;
}

void Game::setenemy()
{
    Enemy1 * e1 = new Enemy1();
    Enemy1 * e2 = new Enemy1();
    int y1 = qrand()%600;
    int y2 = qrand()%600;
    e1 ->setPos(600,y1);
    e2 ->setPos(600,y2);
    scene->addItem(e1);
    scene->addItem(e2);
}

void Game::back()
{
    setScene(scene_begining);
}

void Game::mousePressEvent(QMouseEvent *event){
    if(event->x()<600){

    if(id == 1){
    // create minion1
    Minion1 * minion = new Minion1();
    minion->setPos(event->x()-250,event->y());
    scene->addItem(minion);
    }
    else if(id == 2){
    // create minion2
    Minion2 * minion = new Minion2();
    minion->setPos(event->x()-250,event->y());
    scene->addItem(minion);
    }
    if(id == 3){
    // create a minion3
    Minion3 * minion = new Minion3();
    minion->setPos(event->x()-250,event->y());
    scene->addItem(minion);
    }
    if(id == 4){
    // create a minion4
    Minion4 * minion = new Minion4();
    minion->setPos(event->x()-250,event->y());
    scene->addItem(minion);
    }
    if(id == 5){
    // create a ENEMY1
    Enemy1 * minion = new Enemy1();
    minion->setPos(event->x()-250,event->y());
    scene->addItem(minion);
    }
    id = 0;
}
}
