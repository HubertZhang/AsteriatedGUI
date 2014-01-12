#include "starbg.h"
#include <QString>
StarBG::StarBG(QWidget *parent) :
QLabel(parent)
{
    this->setMinimumSize(1366,768);
    sign = true;
    frame = 0;
    refreshSpeed = -1;
    for (int i = 0; i<40; i ++) {
        starBGArray[i].load(QString(":/StarBG/StarBG_000%1").arg(QString::number(i),2,QChar('0')));
    }
}
void StarBG::updatePic()
{
    refreshSpeed ++;
    if(refreshSpeed % 5 == 0)
    {
        refreshSpeed = 1;
        return ;
    }
    if(sign && frame == 39)
    {
        sign = false;
    }
    if(!sign && frame == 0)
    {
        sign = true;
    }
    if(sign)
    {
        frame ++;
    }
    if(!sign)
    {
        frame --;
    }
}

void StarBG::paint(QPaintEvent *event, QPainter *painter)
{
    painter->drawPixmap(0,0,1366,768,starBGArray[frame]);
}
