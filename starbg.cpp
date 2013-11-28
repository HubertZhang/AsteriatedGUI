#include "starbg.h"
#include <QString>
StarBG::StarBG(QWidget *parent) :
    QWidget(parent)
{
    QString s;
    sign = true;
    frame = 0;
    refreshSpeed = -1;
    for(int i = 0;i < 40;i++)
    {
        if(i < 10)
        {
            s.sprintf(":/StarBG/StarBG_0000%d.png",i);
            starBGArray[i] = new QPixmap();
            starBGArray[i]->load(s);
            continue;
        }
        s.sprintf(":/StarBG/StarBG_000%d.png",i);
        starBGArray[i] = new QPixmap();
        starBGArray[i]->load(s);
    }
}
void StarBG::paint(QPaintEvent *event, QPainter *painter)
{
    refreshSpeed ++;
    if(refreshSpeed % 2 != 0)
    {
        refreshSpeed = 1;
        painter->drawPixmap(0,0,1366,768,*starBGArray[frame]);
        return ;
    }
    painter->drawPixmap(0,0,1366,768,*starBGArray[frame]);
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
