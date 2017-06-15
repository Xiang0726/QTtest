#include "fog.h"
#include "Minion1.h"
#include "Minion2.h"
#include "Minion3.h"
#include "Minion4.h"
#include "Game.h"
#include <QPixmap>
#include<QObject>
#include<QGraphicsScene>
#include<QList>

fog::fog()
{
    setPixmap(QPixmap(":images/Fog.jpg"));


}

fog::~fog()
{

}

