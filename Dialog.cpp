#include "Dialog.h"
#include <QInputDialog>
#include"Game.h"
#include<QDebug>

QString InputDlg::a="gsn9646141";
QString InputDlg::b="ss6266942";
QString InputDlg::aa="123";
QString InputDlg::bb="456";

extern Game * game;

InputDlg::InputDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(QStringLiteral("登入"));
    nameLabel1 = new QLabel;
    nameLabel1->setText(tr("帳號："));
    nameLabel2 = new QLabel;
    nameLabel2->setText(tr(""));
    nameLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    nameBtn = new QPushButton;
    nameBtn->setText(tr("輸入帳號"));

    passwordLabel1 = new QLabel;
    passwordLabel1->setText(tr("密碼："));
    passwordLabel2 = new QLabel;
    passwordLabel2->setText(tr(""));
    passwordLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    passwordBtn = new QPushButton;
    passwordBtn->setText(tr("輸入密碼"));

    sign_inBtn = new QPushButton();
    sign_inBtn->setText(tr("登入"));


    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nameLabel1,0,0);
    mainLayout->addWidget(nameLabel2,0,1);
    mainLayout->addWidget(nameBtn,0,2);

    mainLayout->addWidget(passwordLabel1,1,0);
    mainLayout->addWidget(passwordLabel2,1,1);
    mainLayout->addWidget(passwordBtn,1,2);

    mainLayout->addWidget(sign_inBtn,3,1);

    connect(nameBtn,SIGNAL(clicked()),this,SLOT(InputName()));
    connect(passwordBtn,SIGNAL(clicked()),this,SLOT(InputPassword()));
    connect(sign_inBtn,SIGNAL(clicked()),this,SLOT(sign_in()));
}

void InputDlg::InputName(){

    bool ok;
    QString text = QInputDialog::getText(this,tr("帳號"),tr("請輸入帳號："),QLineEdit::Normal,nameLabel2->text(),&ok);
    if (ok && !text.isEmpty()){
        nameLabel2->setText(text);}
       {
        if (a==text){ c=1; }
        else{c=0;}
       }
       {
        if (aa==text){ cc=1; }
        else{cc=0;}
       }
}
void InputDlg::InputPassword(){
    bool okk;
QString text1 = QInputDialog::getText(this,tr("密碼"),tr("請輸入密碼："),QLineEdit::Normal,passwordLabel2->text(),&okk);
if (okk && !text1.isEmpty()){
    passwordLabel2->setText(text1);}
   {
    if (b==text1){ ccc=1; }
    else{ccc=0;}
   }
   {
    if (bb==text1){ cccc=1; }
    else{cccc=0;}
   }
}

void InputDlg::sign_in(){
    if(c+ccc==2){
        game->show();
            }
    else if(cc+cccc==2){
        game->show();
                  }
}
