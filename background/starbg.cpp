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
void StarBG::update()
{
    refreshSpeed ++;
    if(refreshSpeed % 2 != 0)
    {
        this->setPixmap(starBGArray[frame]);
        refreshSpeed = 1;
        this->setPixmap(starBGArray[frame]);
        return ;
    }
    this->setPixmap(starBGArray[frame]);
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
