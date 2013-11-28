#include "picbutton.h"
#include <cstdlib>
#include <QString>
#include <iostream>
PicButton::PicButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canBe)
{
    QString s;
    canBeClicked = canBe;
    s.sprintf(":/button/buttonNotClicked%d.png",buttonKind);
    notClickedMap = new QPixmap();
    notClickedMap->load(s);
    clickedMap = new QPixmap();
    if(buttonKind < 25)
    {
        s.sprintf(":/character/character%d.png",buttonKind);
        //system("pause");
        clickedMap->load(s);
        notClickedMap->load(s);
    }
    else
    {
        s.sprintf(":/button/buttonClicked%d.png",buttonKind);
        clickedMap->load(s);
    }
    switch(paraW)
    {
        case 100:
        {
            s.sprintf(":/character/buttonFrame100.png");
            break;
        }
        case 50:
        {
            if(paraH == 42)
            {
                s.sprintf(":/character/buttonFrame50.png");
                break;
            }
            else
            {
                s.sprintf(":/character/cureFrame.png");
            }
        }
        case 48:
        {
            s.sprintf(":/character/cardFrameX.png");
        }
        default:
        {
            s.sprintf(":/character/choosenFrame.png");
        }
    }
    frame = new QPixmap();
    frame->load(s);
    isClicked = false;
    canBeClicked = canBe;
    xp = paraX;
    yp = paraY;
    width =  paraW;
    height = paraH;
}//buttonKind from 1 to 31:For characterPic;
void PicButton::isThisClicked(int x,int y)
{
    if(canBeClicked)
    {
        if(x > xp && x < (xp + width))
        {
            if(y > yp && y < (yp + height))
            {
                isClicked = !isClicked;
                //system("pause");
                if(isClicked)
                {
                    emit changeClicked();
                }
                else
                {
                    emit notClicked();
                }
            }
        }
    }
}
void PicButton::paint(QPaintEvent *event,QPainter* painter)
{
    if(!canBeClicked)
    {
        painter->drawPixmap(xp,yp,width,height,*notClickedMap);
    }
    else
    {
        painter->drawPixmap(xp,yp,width,height,*clickedMap);
    }
    if(isClicked)
    {
        painter->drawPixmap(xp,yp,width,height,*frame);
    }
}
void PicButton::cancelX()
{
    isClicked = false;
}
void PicButton::recover()
{
    isClicked = true;
}
void PicButton::cancelClick()
{
    canBeClicked = false;
    isClicked  = false;
}
void PicButton::recoverClick()
{
    canBeClicked = true;
}
