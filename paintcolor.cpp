#include "paintcolor.h"
#include <cstdlib>
PaintColor::PaintColor(int color[6],QWidget *parent) :
    QWidget(parent)
{
    width = 165;
    height = 231;
    xp[0] = 120; yp[0] = 269;
    xp[1] = 260; yp[1] = 2;
    xp[2] = 505; yp[2] = 2;
    xp[3] = 750; yp[3] = 2;
    xp[4] = 890; yp[4] = 269;
    xp[5] = 190, yp[5] = 537;
    redFrame = new QPixmap();
    blueFrame = new QPixmap();
    frame = new QPixmap();
    redFrame->load(":/character/redCharacterFrame.png");
    blueFrame->load(":/character/blueCharacterFrame.png");
    if(color[5])
    {
        frame->load(":/Frame/BlueFrame.png");
    }
    else
    {
        frame->load(":/Frame/RedFrame.png");
    }
    for(int i = 0;i < 6;i++)
    {
        pColor[i] = color[i];
    }
}
void PaintColor::paint(QPaintEvent *event, QPainter *painter)
{
    painter->drawPixmap(0,0,frame->width(),frame->height(),*frame);
    for(int i = 0;i < 6;i++)
    {
        if(pColor[i] == 0)
        {
            painter->drawPixmap(xp[i],yp[i],width,height,*redFrame);
        }
        else
        {
            painter->drawPixmap(xp[i],yp[i],width,height,*blueFrame);
        }
    }
}

