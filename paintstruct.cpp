#include "paintstruct.h"
#include <QString>
#include <QPainter>
#include <cstdlib>
#include <iostream>
QPixmap Character::poisonPic(":/character/poison.png");
QPixmap Character::weakPic(":/character/weak.png");
QPixmap Character::sheildPic(":/character/sheild.png");
QPixmap Character::sealPic[6] = {QPixmap(":/character/seal0.png"),QPixmap(":/character/seal1.png"),QPixmap(":/character/seal2.png"),QPixmap(":/character/seal3.png"),QPixmap(":/character/seal4.png"),QPixmap(":/character/seal5.png")};
QPixmap PaintStruct::crystalPic(":/character/crystal.png");
QPixmap PaintStruct::gemPic(":/character/gem.png");
Character::Character(int characterNum,int place,int color)
{
    //setGeometry(GEO_CHARACTER_X[place], GEO_CHARACTER_Y[place], <#int aw#>, <#int ah#>);
    this->yellow = 0;
    this->blue = 0;
    this->characterNum = characterNum;
    this->blueExist = getBlue(characterNum);
    this->yellowExist = getYellow(characterNum);
    this->characterPic = new CharacterButton(characterNum,place,this);
    //TODO:
    //        this->choosenFrame = new QPixmap();
    //        s.sprintf(":/character/choosenFrame.png");
    //        this->choosenFrame->load(s);
    this->color = color;
    this->crystal = 0;
    //this->crystal = getCrystal(this->characterNum);
    this->cure = 0;
    this->cureLimit = getCureLimit(this->characterNum);
    this->energeLimit = getEnergyLimit(this->characterNum);
    this->gem = 0;
    this->statusNum = 0;
    this->activated = false;
    this->canBeActivated = ifActivated(this->characterNum);
    this->cardNum = 0;
    this->cardLimit = 6;
    
    
    for(int j = 0;j < 10;j++)
    {
        statusBar[j].setParent(this);
        statusBar[j].setGeometry(157 - 16,10 + 30 * j , 36, 36);
    }
}

PaintStruct::PaintStruct(int information[15],QWidget* parent,int yourX)
{
//    paintArrow = false;
    arrowNum = 0;
    grailRed = 0;
    grailBlue = 0;
    gemRed = 0;
    gemBlue = 0;
    crystalRed = 0;
    crystalBlue = 0;
    moraleRed = 15;
    moraleBlue = 15;
    redMoralePic.setPixmap(QString(":/morale/red%1.png").arg(moraleRed));
    blueMoralePic.setPixmap(QString(":/morale/blue%1.png").arg(moraleBlue));
    redMoralePic.setGeometry(GEO_MORALE_X, GEO_MORALE_RED_Y, GEO_MORALE_W, GEO_MORALE_H);
    blueMoralePic.setGeometry(GEO_MORALE_X, GEO_MORALE_BLUE_Y, GEO_MORALE_W, GEO_MORALE_H);
    

    
    for (int i = 0; i<5; i++) {
        redGrailPic[i].setGeometry(GEO_GRAIL_X, GEO_GRAIL_RED_Y+i*GEO_GRAIL_YOFFSET, GEO_GRAIL_W, GEO_GRAIL_H);
        blueGrailPic[i].setGeometry(GEO_GRAIL_X, GEO_GRAIL_RED_Y+i*GEO_GRAIL_YOFFSET, GEO_GRAIL_W, GEO_GRAIL_H);
        redGrailPic[i].setPixmap(QPixmap(":/character/grail.png"));
        blueGrailPic[i].setPixmap(QPixmap(":/character/grail.png"));
        redGrailPic[i].setVisible(false);
        blueGrailPic[i].setVisible(false);

        blueGrailPic[i].setGeometry(GEO_GRAIL_X, GEO_GRAIL_RED_Y+i*GEO_GRAIL_YOFFSET, GEO_GRAIL_W, GEO_GRAIL_H);
        redStonePic[i].setGeometry(GEO_STONE_X, GEO_STONE_RED_Y+i*GEO_STONE_YOFFSET, GEO_STONE_W, GEO_STONE_H);
        blueStonePic[i].setGeometry(GEO_STONE_X, GEO_STONE_RED_Y+i*GEO_STONE_YOFFSET, GEO_STONE_W, GEO_STONE_H);
    }
    for(int i = 0;i < 6;i++)
    {
        
        gameCharacter[i] = new Character(information[i],i,information[i+6]);
    }


//    arrowX[0] = gameCharacter[0]->xp +157 + 2 + 10;
//    for(int j = 1;j < 4;j++)
//    {
//        arrowX[j] = (gameCharacter[j]->xp * 2 + 158)/2 - 18;
//    }
//    arrowX[4] = gameCharacter[4]->xp - 2 - 10 - 36;
//    arrowX[5] = (gameCharacter[5]->xp * 2 + 158)/2 - 18;
//    arrowY[0] = (gameCharacter[0]->yp * 2 + 224)/2 - 18;
//    for(int j = 1;j < 4;j++)
//    {
//        arrowY[j] = (gameCharacter[j]->yp + 2 + 10 + 223);
//    }
//    arrowY[4] = (gameCharacter[4]->yp * 2 + 224)/2 - 18;
//    arrowY[5] = gameCharacter[5]->yp - 2 - 10 - 36;


    
//    cardFrame = new QPixmap();
//    gem->load(":/character/gem.png");
//    crystal->load(":/character/crystal.png");
//    grail->load(":/character/grail.png");
//    weakPic->load(":/character/weak.png");
//    poisonPic->load(":/character/poison.png");
//    sheildPic->load(":/character/sheild.png");
//    soulB->load(":/character/SoulB.png");
//    soulY->load(":/character/SoulY.png");
//    cardFrame->load(":/character/CardFrame.png");
//    cardList = new CardList();
}

int getCrystal(int characterNum)
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
int getCureLimit(int characterNum)
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
int getEnergyLimit(int characterNum)
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
bool ifActivated(int characterNum)
{
    switch(characterNum)
    {
        case 5:
        case 6:
        case 9:
        case 14:
        case 16:
        case 21:
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
bool getBlue(int characterNum)
{
    switch(characterNum)
    {
        case 19:
        case 21:
        case 22:
        {
            return true;
        }
    }
    return false;
}
bool getYellow(int characterNum)
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

void Character::paintEvent(QPaintEvent *event)
{
    //TODO
    cureLabel.setText(QString("%1/%2").arg(cure,cureLimit));
    gemLabel.setText(QString("%1/%2").arg(gem,energeLimit));
    crystalLabel.setText(QString("%1/%2").arg(crystal,energeLimit));
//        if(i > 0 && i < 4)
//        {
//            painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[4]);
//            painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[4]);
//            int gemNum = gameCharacter[i]->gem;
//            int crystalNum = gameCharacter[i]->crystal;
//            int cureNum = gameCharacter[i]->cure;
//            int offset = 30;
//            int num = 0;
//            while(gemNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[0]);
//                num ++;
//                gemNum --;
//            }
//            while(crystalNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[1]);
//                num ++;
//                crystalNum --;
//            }
//            num = 0;
//            while(cureNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp +95 - 3 + offset * num,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[2]);
//                num ++;
//                cureNum --;
//            }
//        }
//        else
//        {
//            painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[4]);
//            painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[4]);
//            int gemNum = gameCharacter[i]->gem;
//            int crystalNum = gameCharacter[i]->crystal;
//            int cureNum = gameCharacter[i]->cure;
//            int offset = 30;
//            int num = 0;
//            while(gemNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[0]);
//                num ++;
//                gemNum --;
//            }
//            while(crystalNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[1]);
//                num ++;
//                crystalNum --;
//            }
//            num = 0;
//            while(cureNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp +95 - 3 + offset * num,gameCharacter[i]->yp - 15,36,36,*attribute[2]);
//                num ++;
//                cureNum --;
//            }
//        }
//    }
//    else if(gameCharacter[i]->energeLimit == 4)
//    {
//        if(i > 0 && i < 4)
//        {
//            painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[2]);
//            int gemNum = gameCharacter[i]->gem;
//            int crystalNum = gameCharacter[i]->crystal;
//            int cureNum = gameCharacter[i]->cure;
//            int offset = 30;
//            int num = 0;
//            while(gemNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[0]);
//                num ++;
//                gemNum --;
//            }
//            while(crystalNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[1]);
//                num ++;
//                crystalNum --;
//            }
//            painter->drawPixmap(gameCharacter[i]->xp + 125 - 3 + 7,gameCharacter[i]->yp - 15 + 226 - 10,36,36,*number[cureNum]);
//        }
//        else
//        {
//            painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 95 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 125 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[2]);
//            int gemNum = gameCharacter[i]->gem;
//            int crystalNum = gameCharacter[i]->crystal;
//            int cureNum = gameCharacter[i]->cure;
//            int offset = 30;
//            int num = 0;
//            while(gemNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[0]);
//                num ++;
//                gemNum --;
//            }
//            while(crystalNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[1]);
//                num ++;
//                crystalNum --;
//            }
//            painter->drawPixmap(gameCharacter[i]->xp + 125 - 3 + 7,gameCharacter[i]->yp - 15 - 10,36,36,*number[cureNum]);
//        }
//    }
//    else
//    {
//        if(i > 0 && i < 4)
//        {
//            painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 110 - 3,gameCharacter[i]->yp - 15 + 226,36,36,*attribute[2]);
//            int gemNum = gameCharacter[i]->gem;
//            int crystalNum = gameCharacter[i]->crystal;
//            int cureNum = gameCharacter[i]->cure;
//            int offset = 30;
//            int num = 0;
//            while(gemNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[0]);
//                num ++;
//                gemNum --;
//            }
//            while(crystalNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19 + 226,36,36,*attribute[1]);
//                num ++;
//                crystalNum --;
//            }
//            painter->drawPixmap(gameCharacter[i]->xp + 110 - 3 + 7,gameCharacter[i]->yp - 15 + 226 - 10,36,36,*number[cureNum]);
//        }
//        else
//        {
//            painter->drawPixmap(gameCharacter[i]->xp + 5 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 35 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 65 - 3,gameCharacter[i]->yp - 19,36,36,*attribute[3]);
//            painter->drawPixmap(gameCharacter[i]->xp + 110 - 3,gameCharacter[i]->yp - 15,36,36,*attribute[2]);
//            int gemNum = gameCharacter[i]->gem;
//            int crystalNum = gameCharacter[i]->crystal;
//            int cureNum = gameCharacter[i]->cure;
//            int offset = 30;
//            int num = 0;
//            while(gemNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[0]);
//                num ++;
//                gemNum --;
//            }
//            while(crystalNum != 0)
//            {
//                painter->drawPixmap(gameCharacter[i]->xp + 5 - 3 + offset * num,gameCharacter[i]->yp - 19,36,36,*attribute[1]);
//                num ++;
//                crystalNum --;
//            }
//            painter->drawPixmap(gameCharacter[i]->xp + 110 - 3 + 7,gameCharacter[i]->yp - 15 - 10,36,36,*number[cureNum]);
//        }
//    }
//    if(i > 0 && i < 4)
//    {
//        painter->drawPixmap(SoulYX[i] - 17,SoulYY[i] - 50,36,36,*number[gameCharacter[i]->cardNum]);
//        painter->drawPixmap(SoulYX[i] - 2,SoulYY[i] - 50,36,36,*slash);
//        painter->drawPixmap(SoulYX[i] + 13,SoulYY[i] - 50,36,36,*number[gameCharacter[i]->cardLimit]);
//    }
//    else
//    {
//        painter->drawPixmap(SoulYX[i] - 65,SoulYY[i],36,36,*number[gameCharacter[i]->cardNum]);
//        painter->drawPixmap(SoulYX[i] - 50,SoulYY[i],36,36,*slash);
//        painter->drawPixmap(SoulYX[i] - 35,SoulYY[i],36,36,*number[gameCharacter[i]->cardLimit]);
//    }
    if(yellowExist)
    {
        //TODO
//        painter->drawPixmap(SoulYX[i],SoulYY[i],36,36,*soulY);
//        painter->drawPixmap(SoulYX[i] + 7,SoulYY[i] - 10,36,36,*number[gameCharacter[i]->yellow]);
    }
    if(blueExist)
    {
        //TODO
//        painter->drawPixmap(SoulBX[i],SoulBY[i],36,36,*soulB);
//        painter->drawPixmap(SoulBX[i] + 7,SoulBY[i] - 10,36,36,*number[gameCharacter[i]->blue]);
    }
    for(int j = 0;j < statusNum; j ++)
    {
        statusBar[j].setVisible(true);
        switch(cardlist.getName(status[j]))
        {
            case weak:
            {
                statusBar[j].setPixmap(weakPic);
                break;
            }
            case poison:
            {
                statusBar[j].setPixmap(poisonPic);
                break;
            }
            case shield:
            {
                statusBar[j].setPixmap(sheildPic);
                break;
            }
            case fiveBound:
            {
                statusBar[j].setPixmap(sealPic[5]);
                break;
            }
            default://五系封印
            {
                statusBar[j].setPixmap(sealPic[cardlist.getSkillOne(status[j]) - 41]);
                break;
            }
        }
    }
    for (int i = statusNum; i<10; i++) {
        statusBar[i].setVisible(false);
    }
}

void PaintStruct::paintEvent(QPaintEvent *event)
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

    while(teamGrailRed != 0)
    {
        redGrailPic[count].setVisible(true);
        count ++;
        teamGrailRed --;
    }
    count = 0;
    while(teamGrailBlue != 0)
    {
        blueGrailPic[count].setVisible(true);
        count ++;
        teamGrailBlue --;
    }
    count = 0;
    while(teamGemRed != 0)
    {
        redStonePic[count].setVisible(true);
        redStonePic[count].setPixmap(gemPic);
        count ++;
        teamGemRed --;
    }
    while(teamCrystalRed != 0)
    {
        redStonePic[count].setVisible(true);
        redStonePic[count].setPixmap(crystalPic);
        count ++;
        teamCrystalRed --;
    }
    while (count!=4) {
        redStonePic[count].setVisible(false);
        count++;
    }
    count = 0;
    while(teamGemBlue != 0)
    {
        blueStonePic[count].setVisible(true);
        blueStonePic[count].setPixmap(gemPic);
        count ++;
        teamGemBlue --;
    }
    while(teamCrystalBlue != 0)
    {
        blueStonePic[count].setVisible(true);
        blueStonePic[count].setPixmap(crystalPic);
        count ++;
        teamCrystalBlue --;
    }
    while (count!=4) {
        redStonePic[count].setVisible(false);
        count++;
    }
}
