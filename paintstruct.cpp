#include "paintstruct.h"
#include <QString>
#include <QPainter>
#include <cstdlib>
#include <iostream>
PaintStruct::PaintStruct(int information[15],QWidget* parent,int yourX)
{
    yourSite = yourX;
    QString s;
    for(int i = 0;i < 6;i ++)
    {
        gameCharacter[i] = new character();
    }
    for(int i = 0;i < 17;i ++)
    {
        redNum[i] = new QPixmap();
        blueNum[i] = new QPixmap();
        s.sprintf(":/morale/red%d.png",i);
        redNum[i]->load(s);
        s.sprintf(":/morale/blue%d.png",i);
        blueNum[i]->load(s);
    }
    for(int i = 0;i < 17;i ++)
    {
        s.sprintf(":/number/%d.png",i);
        number[i] = new QPixmap();
        number[i]->load(s);
    }
    slash = new QPixmap();
    slash->load(":/number/slash.png");
    gameCharacter[0]->xp = 124; gameCharacter[0]->yp = 273;
    gameCharacter[1]->xp = 264; gameCharacter[1]->yp = 6;
    gameCharacter[2]->xp = 509; gameCharacter[2]->yp = 6;
    gameCharacter[3]->xp = 754; gameCharacter[3]->yp = 6;
    gameCharacter[4]->xp = 894; gameCharacter[4]->yp = 273;
    gameCharacter[5]->xp = 194; gameCharacter[5]->yp = 541;
    for(int i = 0;i < 6;i++)
    {
        gameCharacter[i]->yellow = 0;
        gameCharacter[i]->blue = 0;
        gameCharacter[i]->blueExist = getBlue(gameCharacter[i]->characterNum);
        gameCharacter[i]->characterNum = information[i];
        gameCharacter[i]->blueExist = getBlue(gameCharacter[i]->characterNum);
        gameCharacter[i]->yellowExist = getYellow(gameCharacter[i]->characterNum);
        gameCharacter[i]->characterPic = new PicButton(gameCharacter[i]->characterNum,gameCharacter[i]->xp,gameCharacter[i]->yp,157,223,false);
        gameCharacter[i]->choosenFrame = new QPixmap();
        s.sprintf(":/character/choosenFrame.png");
        gameCharacter[i]->choosenFrame->load(s);
        gameCharacter[i]->color = information[i+6];
        gameCharacter[i]->crystal = 0;
        //gameCharacter[i]->crystal = getCrystal(gameCharacter[i]->characterNum);
        gameCharacter[i]->cure = 0;
        gameCharacter[i]->cureLimit = getCureLimit(gameCharacter[i]->characterNum);
        gameCharacter[i]->energeLimit = getEnergyLimit(gameCharacter[i]->characterNum);
        gameCharacter[i]->gem = 0;
        gameCharacter[i]->statusNum = 0;
        gameCharacter[i]->activated = false;
        gameCharacter[i]->canBeActivated = ifActivated(gameCharacter[i]->characterNum);
        gameCharacter[i]->cardNum = 0;
        gameCharacter[i]->cardLimit = 6;
        gameCharacter[i]->blue = getBlue(gameCharacter[i]->characterNum);
        if(gameCharacter[i]->canBeActivated)
        {
            gameCharacter[i]->isActivated = new QPixmap();
            s.sprintf(":/character/character%dActivated.png",information[i]);
            gameCharacter[i]->isActivated->load(s);
        }
        if(i == 0 || i == 4)
        {
            SoulYX[i] = gameCharacter[i]->xp + 66;
            SoulBX[i] = gameCharacter[i]->xp + 103 ;
            SoulYY[i] = gameCharacter[i]->yp + 223 + 2 - 18;
            SoulBY[i] = gameCharacter[i]->yp + 223 + 2 - 18;
        }
        int offsetYQUQ = 50;
        if(i == 1)
        {
            SoulYX[i] = gameCharacter[i]->xp + 157 + 2 - 18;
            SoulBX[i] = gameCharacter[i]->xp + 157 + 2 - 18;
            SoulYY[i] = gameCharacter[i]->yp + offsetYQUQ * 2;
            SoulBY[i] = gameCharacter[i]->yp + offsetYQUQ * 3;
        }
        if(i == 2 || i == 3)
        {
            SoulYX[i] = gameCharacter[i]->xp - 2 - 18;
            SoulBX[i] = gameCharacter[i]->xp - 2 - 18;
            SoulYY[i] = gameCharacter[i]->yp + offsetYQUQ * 2;
            SoulBY[i] = gameCharacter[i]->yp + offsetYQUQ * 3;
        }
        if(i == 5)
        {
            SoulYX[i] = gameCharacter[i]->xp + 157 + 4 + 66;
            SoulBX[i] = gameCharacter[i]->xp + 157 + 4 + 103;
            SoulYY[i] = gameCharacter[i]->yp - 2 - 20;
            SoulBY[i] = gameCharacter[i]->yp - 2 - 20;
        }
    }
    for(int j = 0;j < 6;j++)
    {
        attribute[j] = new QPixmap();
        s.sprintf(":/characterAttribute/attribute%d.png",j);
        attribute[j]->load(s);
    }
    for(int j = 0;j < 4;j++)
    {
        arrow[j] = new QPixmap();
        s.sprintf(":/character/arrow%d.png",j);
        arrow[j]->load(s);
    }
    arrowX[0] = gameCharacter[0]->xp +157 + 2 + 10;
    for(int j = 1;j < 4;j++)
    {
        arrowX[j] = (gameCharacter[j]->xp * 2 + 158)/2 - 18;
    }
    arrowX[4] = gameCharacter[4]->xp - 2 - 10 - 36;
    arrowX[5] = (gameCharacter[5]->xp * 2 + 158)/2 - 18;
    arrowY[0] = (gameCharacter[0]->yp * 2 + 224)/2 - 18;
    for(int j = 1;j < 4;j++)
    {
        arrowY[j] = (gameCharacter[j]->yp + 2 + 10 + 223);
    }
    arrowY[4] = (gameCharacter[4]->yp * 2 + 224)/2 - 18;
    arrowY[5] = gameCharacter[5]->yp - 2 - 10 - 36;
    paintArrow = false;
    arrowNum = 0;
    grailRed = 0;
    grailBlue = 0;
    gemRed = 0;
    gemBlue = 0;
    crystalRed = 0;
    crystalBlue = 0;
    moraleRed = 15;
    moraleBlue = 15;
    gem = new QPixmap();
    crystal = new QPixmap();
    grail = new QPixmap();
    weakPic = new QPixmap();
    poisonPic = new QPixmap();
    sheildPic = new QPixmap();
    soulB = new QPixmap();
    soulY = new QPixmap();
    cardFrame = new QPixmap();
    gem->load(":/character/gem.png");
    crystal->load(":/character/crystal.png");
    grail->load(":/character/grail.png");
    weakPic->load(":/character/weak.png");
    poisonPic->load(":/character/poison.png");
    sheildPic->load(":/character/sheild.png");
    soulB->load(":/character/SoulB.png");
    soulY->load(":/character/SoulY.png");
    cardFrame->load(":/character/CardFrame.png");
    cardList = new CardList();
}
int PaintStruct::getCrystal(int characterNum)
{
    switch(characterNum)
    {
        case 14:
        case 21:
        {
            return 2;
        }
        default:
        {
            return 0;
        }
    }
}
int PaintStruct::getCureLimit(int characterNum)
{
    switch(characterNum)
    {
        case 13:
        {
            return 5;
        }
        case 15:
        {
            return 6;
        }
        case 27:
        {
            return 4;
        }
        default:
        {
            return 2;
        }
    }
}
int PaintStruct::getEnergyLimit(int characterNum)
{
    switch(characterNum)
    {
        case 17:
        {
            return 4;
        }
        default:
        {
            return 3;
        }
    }
}
bool PaintStruct::ifActivated(int characterNum)
{
    switch(characterNum)
    {
        case 5:
        case 6:
        case 9:
        case 14:
        case 16:
        case 23:
        case 24:
        case 26:
        case 30:
        case 31:
        {
            return true;
        }
    }
    return false;
}
bool PaintStruct::getBlue(int characterNum)
{
    switch(characterNum)
    {
        case 21:
        case 22:
        {
            return true;
        }
    }
    return false;
}
bool PaintStruct::getYellow(int characterNum)
{
    switch(characterNum)
    {
        case 11:
        case 14:
        case 16:
        case 19:
        case 20:
        case 21:
        case 22:
        {
            return true;
        }
    }
    return false;
}

void PaintStruct::paint(QPaintEvent *event, QPainter *painter)
{
    int teamGemRed = gemRed;
    int teamGemBlue = gemBlue;
    int teamCrystalRed = crystalRed;
    int teamCrystalBlue = crystalBlue;
    int teamGrailRed = grailRed;
    int teamGrailBlue = grailBlue;
    //int xOffset = 46;
    int yOffset = 52;
    int count = 0;
    painter->drawPixmap(39,321,50,50,*redNum[moraleRed]);
    painter->drawPixmap(39,392,50,50,*blueNum[moraleBlue]);
    while(teamGrailRed != 0)
    {
        painter->drawPixmap(15,67 + yOffset * count,50,50,*grail);
        count ++;
        teamGrailRed --;
    }
    count = 0;
    while(teamGrailBlue != 0)
    {
        painter->drawPixmap(15,443 + yOffset * count,50,50,*grail);
        count ++;
        teamGrailBlue --;
    }
    count = 0;
    while(teamGemRed != 0)
    {
        painter->drawPixmap(15 + 46,67 + yOffset * count,50,50,*gem);
        count ++;
        teamGemRed --;
    }
    while(teamCrystalRed != 0)
    {
        painter->drawPixmap(15 + 46,67 + yOffset * count,50,50,*crystal);
        count ++;
        teamCrystalRed --;
    }
    count = 0;
    while(teamGemBlue != 0)
    {
        painter->drawPixmap(15 + 46,443 + yOffset * count,50,50,*gem);
        count ++;
        teamGemBlue --;
    }
    while(teamCrystalBlue != 0)
    {
        painter->drawPixmap(15 + 46,443 + yOffset * count,50,50,*crystal);
        count ++;
        teamCrystalBlue --;
    }
    //Activate painting!
    //
    //
    for(int i = 0;i < 6;i++)
    {
        gameCharacter[i]->characterPic->paint(event,painter);
    }
    for(int i = 0;i < 6;i++)
    {
        if(gameCharacter[i]->cureLimit == 2 && gameCharacter[i]->energeLimit == 3 && gameCharacter[i]->cure < 3)
        {
            if(i > 0 && i < 4)
            {
                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[4]);
                painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[4]);
                int gemNum = gameCharacter[i]->gem;
                int crystalNum = gameCharacter[i]->crystal;
                int cureNum = gameCharacter[i]->cure;
                int offset = 30;
                int num = 0;
                while(gemNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[0]);
                    num ++;
                    gemNum --;
                }
                while(crystalNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[1]);
                    num ++;
                    crystalNum --;
                }
                num = 0;
                while(cureNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp +95 - 3 + offset * num,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[2]);
                    num ++;
                    cureNum --;
                }
            }
            else
            {
                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[4]);
                painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[4]);
                int gemNum = gameCharacter[i]->gem;
                int crystalNum = gameCharacter[i]->crystal;
                int cureNum = gameCharacter[i]->cure;
                int offset = 30;
                int num = 0;
                while(gemNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[0]);
                    num ++;
                    gemNum --;
                }
                while(crystalNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[1]);
                    num ++;
                    crystalNum --;
                }
                num = 0;
                while(cureNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp +95 - 3 + offset * num,gameCharacter[i]->yp - 15,36,36,*attribute[2]);
                    num ++;
                    cureNum --;
                }
            }
        }
        else if(gameCharacter[i]->energeLimit == 4)
        {
            if(i > 0 && i < 4)
            {
                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[2]);
                int gemNum = gameCharacter[i]->gem;
                int crystalNum = gameCharacter[i]->crystal;
                int cureNum = gameCharacter[i]->cure;
                int offset = 30;
                int num = 0;
                while(gemNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[0]);
                    num ++;
                    gemNum --;
                }
                while(crystalNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[1]);
                    num ++;
                    crystalNum --;
                }
                painter->drawPixmap(gameCharacter[i]->xp + 125 - 3 + 7,gameCharacter[i]->yp - 15 + 226 - 10,36,36,*number[cureNum]);
            }
            else
            {
                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[2]);
                int gemNum = gameCharacter[i]->gem;
                int crystalNum = gameCharacter[i]->crystal;
                int cureNum = gameCharacter[i]->cure;
                int offset = 30;
                int num = 0;
                while(gemNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[0]);
                    num ++;
                    gemNum --;
                }
                while(crystalNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[1]);
                    num ++;
                    crystalNum --;
                }
                painter->drawPixmap(gameCharacter[i]->xp + 125 - 3 + 7,gameCharacter[i]->yp - 15 - 10,36,36,*number[cureNum]);
            }
        }
        else
        {
            if(i > 0 && i < 4)
            {
                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 110 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[2]);
                int gemNum = gameCharacter[i]->gem;
                int crystalNum = gameCharacter[i]->crystal;
                int cureNum = gameCharacter[i]->cure;
                int offset = 30;
                int num = 0;
                while(gemNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[0]);
                    num ++;
                    gemNum --;
                }
                while(crystalNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[1]);
                    num ++;
                    crystalNum --;
                }
                painter->drawPixmap(gameCharacter[i]->xp + 110 - 3 + 7,gameCharacter[i]->yp - 15 + 226 - 10,36,36,*number[cureNum]);
            }
            else
            {
                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
                painter->drawPixmap(gameCharacter[i]->xp + 110 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[2]);
                int gemNum = gameCharacter[i]->gem;
                int crystalNum = gameCharacter[i]->crystal;
                int cureNum = gameCharacter[i]->cure;
                int offset = 30;
                int num = 0;
                while(gemNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[0]);
                    num ++;
                    gemNum --;
                }
                while(crystalNum != 0)
                {
                    painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[1]);
                    num ++;
                    crystalNum --;
                }
                painter->drawPixmap(gameCharacter[i]->xp + 110 - 3 + 7,gameCharacter[i]->yp - 15 - 10,36,36,*number[cureNum]);
            }
        }
        if(i > 0 && i < 4)
        {
            painter->drawPixmap(SoulYX[i] - 17,SoulYY[i] - 50,36,36,*number[gameCharacter[i]->cardNum]);
            painter->drawPixmap(SoulYX[i] - 2,SoulYY[i] - 50,36,36,*slash);
            painter->drawPixmap(SoulYX[i] + 13,SoulYY[i] - 50,36,36,*number[gameCharacter[i]->cardLimit]);
        }
        else
        {
            painter->drawPixmap(SoulYX[i] - 65,SoulYY[i],36,36,*number[gameCharacter[i]->cardNum]);
            painter->drawPixmap(SoulYX[i] - 50,SoulYY[i],36,36,*slash);
            painter->drawPixmap(SoulYX[i] - 35,SoulYY[i],36,36,*number[gameCharacter[i]->cardLimit]);
        }
        if(gameCharacter[i]->yellowExist)
        {
            painter->drawPixmap(SoulYX[i],SoulYY[i],36,36,*soulY);
            painter->drawPixmap(SoulYX[i] + 7,SoulYY[i] - 10,36,36,*number[gameCharacter[i]->yellow]);
        }
        if(gameCharacter[i]->blueExist)
        {
            painter->drawPixmap(SoulBX[i],SoulBY[i],36,36,*soulB);
            painter->drawPixmap(SoulBX[i] + 7,SoulBY[i] - 10,36,36,*number[gameCharacter[i]->blue]);
        }
        if(paintArrow)
        {
            switch(arrowNum)
            {
                case 0:
                {
                    painter->drawPixmap(arrowX[arrowNum],arrowY[arrowNum],36,36,*arrow[2]);
                    break;
                }
                case 1:
                case 2:
                case 3:
                {
                    painter->drawPixmap(arrowX[arrowNum],arrowY[arrowNum],36,36,*arrow[0]);
                    break;
                }
                case 4:
                {
                    painter->drawPixmap(arrowX[arrowNum],arrowY[arrowNum],36,36,*arrow[3]);
                    break;
                }
                default:
                {
                    painter->drawPixmap(arrowX[arrowNum],arrowY[arrowNum],36,36,*arrow[1]);
                    break;
                }
            }
        }
        for(int j = 0;j < gameCharacter[i]->statusNum;j ++)
        {
            int offset = 30;
            if(i == 0 ||  i == 2 || i == 3)
            {
                switch(cardList->getName(gameCharacter[i]->status[j]))
                {
                    case weak:
                    {
                        painter->drawPixmap(gameCharacter[i]->xp + 157 - 16,gameCharacter[i]->yp + 10 + offset * j,36,36,*weakPic);
                        break;
                    }
                    case poison:
                    {
                        painter->drawPixmap(gameCharacter[i]->xp + 157 - 16,gameCharacter[i]->yp + 10 + offset * j,36,36,*poisonPic);
                        break;
                    }
                    case shield:
                    {
                        painter->drawPixmap(gameCharacter[i]->xp + 157 - 16,gameCharacter[i]->yp + 10 + offset * j,36,36,*sheildPic);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            else
            {
                switch(cardList->getName(gameCharacter[i]->status[j]))
                {
                    case weak:
                    {
                        painter->drawPixmap(gameCharacter[i]->xp - 20,gameCharacter[i]->yp + 10 + offset * j,36,36,*weakPic);
                        break;
                    }
                    case poison:
                    {
                        painter->drawPixmap(gameCharacter[i]->xp - 20,gameCharacter[i]->yp + 10 + offset * j,36,36,*poisonPic);
                        break;
                    }
                    case shield:
                    {
                        painter->drawPixmap(gameCharacter[i]->xp - 20,gameCharacter[i]->yp + 10 + offset * j,36,36,*sheildPic);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }
}
