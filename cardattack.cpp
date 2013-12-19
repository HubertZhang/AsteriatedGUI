#include "cardattack.h"
#include <cmath>
#include <QMatrix>
#include <QTransform>
#include <iostream>
#include <cstdlib>
#include <QString>
using namespace std;
CardAttack::CardAttack(QWidget *parent) :
    QWidget(parent)
{
    cardList = new CardList();
    paintEnd = false;
    card = new QPixmap();
    window = parent;
    cardCount = 0;
    cardDiscardCount = 0;
    paintOverX = false;
}
void CardAttack::set(int information[])
{
    for(int i = 0;i < 6;i++)
    {
        over[i] = false;
    }
    paintEnd = false;
    paintOverX = false;
    self = false;
    onlyself = false;
    frameCount = -15;
    cardCount = information[2];
    overPaint = cardCount;
    cardDiscardCount = information[3];
    discardXp = 587 - 50 * cardDiscardCount;
    discardYp = 319;
    int firstRecord = 0;
    for(int i = 0;i < information[3];i ++)
    {
        cardDiscardNum[i] = information[i + 4 + information[2]];
        if(!i)
        {
            firstRecord = cardList->getNature(cardDiscardNum[i]);
        }
        else
        {
            if(cardList->getNature(cardDiscardNum[i]) != firstRecord)
            {
                firstRecord = 7;
            }
        }
    }
    QString s("");
    s.sprintf(":/card/card%d",firstRecord);
    card->load(s);
    for(int i = 0;i < cardDiscardCount;i ++)
    {
        cardDiscard[i] = new CardButton(48,discardXp + i * 100,discardYp,99,143,false,cardDiscardNum[i],window);
    }
    initialXp = setCoordinateX(information[1]);
    initialYp = setCoordinateY(information[1]);
    for(int i = 0;i < cardCount;i++)
    {
        endXp[i] = setCoordinateX(information[4 + i]);
        endYp[i] = setCoordinateY(information[4 + i]);
    }
    for(int i = 0;i < cardCount;i++)
    {
        if(endXp[i] == initialXp)
        {
            self = true;
            if(cardCount == 1)
            {
                onlyself = true;
            }
        }
        if(endYp[i] == initialYp)
        {
            if(endXp[i] > initialXp)
            {
                detaX[i] = 40;
                detaY[i] = 0;
                paintAngle[i] = 90;
            }
            else
            if(endXp[i] < initialXp)
            {
                detaX[i] = -40;
                detaY[i] = 0;
                paintAngle[i] = -90;
            }
            else
            {
                detaX[i] = 0;
                detaY[i] = 0;
                paintAngle[i] = 0;
            }
        }
        else
        {
            angle[i] = double((endXp[i] - initialXp))/double((endYp[i] - initialYp));
            paintAngle[i] = -atan(angle[i]) * 180 / 3.14;
            if(paintAngle[i] > 90)
            {
                paintAngle[i] -= 180;
            }
            if(paintAngle[i] < -90)
            {
                paintAngle[i] += 180;
            }
            if(endYp[i] > initialYp)
            {
                detaY[i] = sqrt(double(1600)/(angle[i]*angle[i] + 1));
                detaX[i] = detaY[i] * angle[i];
            }
            else
            {
                detaY[i] = -sqrt((1600)/(angle[i]*angle[i] + 1));
                detaX[i] = detaY[i] * angle[i];
            }
        }
    }
}
void CardAttack::paint(QPaintEvent *event, QPainter *painter)
{
    frameCount++;
    if(frameCount > 0)
    {
        if(onlyself && frameCount == 30)
        {
            paintOverX = true;
        }
        else
        {
            if(self && overPaint == 1)
            {
                paintOverX = true;
            }
        }
        if(!overPaint)
        {
            paintOverX = true;
        }
        for(int i = 0;i < cardDiscardCount;i++)
        {
            cardDiscard[i]->paint(event,painter);
        }
        if(paintEnd)
        {
            return;
        }
        if(paintOverX)
        {
            paintEnd = true;
            emit paintOver();
            return;
        }
        for(int i = 0;i < cardCount;i++)
        {
            if(!over[i])
            {
                QTransform transform;
                transform.rotate(paintAngle[i]);
                painter->drawPixmap(initialXp + frameCount * detaX[i],
                                    initialYp + frameCount * detaY[i],
                                    50 * (fabs(sin(paintAngle[i] * 3.14 / 180)) + fabs(cos(paintAngle[i] * 3.14 / 180))),
                                    50 * (fabs(sin(paintAngle[i] * 3.14 / 180)) + fabs(cos(paintAngle[i] * 3.14 / 180))),
                                    (*card).transformed(transform,Qt::SmoothTransformation));
            }
            else
            {
                continue;
            }
            if(initialXp > endXp[i])
            {
                if(initialXp + (frameCount + 1)*detaX[i] < endXp[i])
                {
                    over[i] = true;
                    overPaint --;
                }
            }
            if(initialXp < endXp[i])
            {
                if(initialXp + (frameCount + 1)*detaX[i] > endXp[i])
                {
                    over[i] = true;
                    overPaint --;
                }
            }
        }
    }
    else
    {
        double rotateRatio = double((15 + frameCount))/15;
        for(int i = 0;i < cardCount;i++)
        {
            QTransform transform;
            transform.rotate(paintAngle[i] * rotateRatio);
            painter->drawPixmap(initialXp,initialYp,50,50,(*card).transformed(transform,Qt::SmoothTransformation));
        }
    }
}
int CardAttack::setCoordinateX(int site)
{
    switch(site)
    {
        case 0:return(124 * 2 + 147)/2 - 25;break;
        case 1:return(264 * 2 + 147)/2 - 25;break;
        case 2:return(509 * 2 + 147)/2 - 25;break;
        case 3:return(754 * 2 + 147)/2 - 25;break;
        case 4:return(894 * 2 + 147)/2 - 25;break;
        case 5:return(194 * 2 + 147)/2 - 25;break;
    }
}
int CardAttack::setCoordinateY(int site)
{
    switch(site)
    {
        case 0:return(273 * 2 + 207)/2 - 25;break;
        case 1:return(6 * 2 + 207)/2 - 25;break;
        case 2:return(6 * 2 + 207)/2 - 25;break;
        case 3:return(6 * 2 + 207)/2 - 25;break;
        case 4:return(273 * 2 + 207)/2 - 25;break;
        case 5:return(541 * 2 + 207)/2 - 25;break;
    }
}
void CardAttack::destroyPic()
{
    for(int i = 0;i < cardDiscardCount;i ++)
    {
        delete cardDiscard[i];
    }
}
