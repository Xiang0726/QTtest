#ifndef DIALOG_H
#define DIALOG_H
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>
#include<QDebug>

class InputDlg : public QDialog
{
    Q_OBJECT

public:
    InputDlg(QWidget* parent=0);
    QLabel *nameLabel1;

    QLabel *nameLabel2;

    QPushButton *nameBtn;

    QLabel *passwordLabel1;

    QLabel *passwordLabel2;

    QPushButton *passwordBtn;

    QPushButton *sign_inBtn;


    QGridLayout *mainLayout;

    static QString a;
    static QString b;
    static QString aa;
    static QString bb;
    int c ;
    int cc;
    int ccc;
    int cccc;


public slots:
    void InputName();
    void InputPassword();
    void sign_in();



};

#endif // DIALOG_H
