#include "adventurer.h"

Adventurer::Adventurer(PaintStruct* paintStruct,QWidget *parent,Window* advenX) :
    CardAndSkill(paintStruct,parent)
{
    cheatCount = 0;
    cheatPaint = false;
    //dialog->init(12);//魔弹融合
    int info[3] = {2,0,0};
    cheat = new AskDialog(info,advenX,paintStruct);
    for(int i = 0;i < 5;i++)
    {
        cheat->number[i]->isClicked = false;
    }
    cheat->ensure->canBeClicked = false;
    cheat->cancel->canBeClicked = false;
    cheat->ensure->isClicked = false;
    cheat->cancel->isClicked = false;
    for(int i = 0;i < 5;i++)
    {
        disconnect(cheat->number[i],SIGNAL(changeClicked()),cheat->ensure,SLOT(recoverClick()));
        connect(cheat->number[i],SIGNAL(changeClicked()),this,SLOT(cheatSet()));
        connect(cheat->number[i],SIGNAL(notClicked()),this,SLOT(cheatReset()));
    }
    magicGroup[0] = new PicButton(95,362,559,100,42,false);
    magicGroup[1] = new PicButton(96,465,559,100,42,false);
    magicGroup[2] = new PicButton(97,568,559,100,42,false);
    for(int i = 0;i < 3;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),magicGroup[i],SLOT(isThisClicked(int,int)));
    }
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            if(i != j)
            {
                connect(magicGroup[i],SIGNAL(changeClicked()),magicGroup[j],SLOT(cancelX()));
            }
        }
    }
    //system("pause");
    connect(magicGroup[0],SIGNAL(changeClicked()),this,SLOT(magicSetZero()));
    connect(magicGroup[1],SIGNAL(changeClicked()),this,SLOT(magicSetOne()));
    connect(magicGroup[2],SIGNAL(changeClicked()),this,SLOT(magicSetTwo()));
    for(int i = 0;i < 3;i++)
    {
        connect(magicGroup[i],SIGNAL(notClicked()),this,SLOT(skillClear()));
    }
}
void Adventurer::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void Adventurer::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
}
void Adventurer::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->isClicked = true;
}
void Adventurer::changeSelfMode(int mode)
{
    for(int i = 0;i < cardNum;i++)
    {
        for(int j = 0;j < cardNum;j++)
        {
            if(i != j)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
            }
        }
        for(int j = 0;j < 6;j++)
        {
            if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
    }
    cancel->canBeClicked = true;
    switch(mode)
    {
        case 4://欺诈响应阶段
        {
            cheatPaint = true;
            cheat->cancel->canBeClicked = false;
            cancel->canBeClicked = false;
            for(int i = 0;i < cardNum;i++)
            {
                cardButton[i]->canBeClicked = true;
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
                    }
                }
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(countPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(countMinus()));
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            break;
        }
        case 5://特殊加工响应阶段
        case 6://偷天换日响应阶段
        {
            cancel->canBeClicked = false;
            ensure->canBeClicked = true;
            break;
        }
    }
}
void Adventurer::paint(QPaintEvent *event, QPainter *painter)
{
    if(cheatPaint)
    {
        cheat->paint(event,painter);
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->paint(event,painter);
    }
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->isClicked = false;
    }
}*/
void Adventurer::skillset()
{
    int detect[7];
    for(int i = 0;i < 7;i++)
    {
        detect[i] = 0;
    }
    for(int i = 0;i < cardNum;i++)
    {
        detect[cardList->getNature(card[i])] ++;
    }
    bool canCheat = false;
    for(int i = 0;i < 7;i++)
    {
        if(detect[i] > 1)
        {
            canCheat = true;
            break;
        }
    }
    magicGroup[0]->canBeClicked = canCheat;
    if(paintStructX->gameCharacter[5]->gem + paintStructX->gameCharacter[5]->crystal > 0)
    {
        magicGroup[1]->canBeClicked = true;
        magicGroup[2]->canBeClicked = true;
    }
}
void Adventurer::skillCancel()
{
    cheat->labelOne->hide();
    cheat->labelTwo->hide();
    for(int i = 0;i < 5;i++)
    {
        cheat->number[i]->isClicked = false;
    }
    cheat->ensure->canBeClicked = false;
    cheat->cancel->canBeClicked = false;
    cheat->ensure->isClicked = false;
    cheat->cancel->isClicked = false;
    cheatPaint = false;
    cheatCount = 0;
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(countPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
}
void Adventurer::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void Adventurer::countPlus()
{
    if(cheatCount == 0)
    {
        cheatCount ++;
        int attribute;
        for(int i = 0;i < cardNum;i++)
        {
            if(cardButton[i]->isClicked)
            {
                attribute = cardList->getNature(card[i]);
                break;
            }
        }
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getNature(card[i]) != attribute)
            {
                cardButton[i]->canBeClicked = false;
            }
        }
        return;
    }
    if(cheatCount == 1)
    {
        cheatCount ++;
        for(int i = 0;i < 5;i++)
        {
            cheat->number[i]->canBeClicked = true;
        }
        return;
    }
    if(cheatCount == 2)
    {
        cheatCount ++;
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isClicked)
            {
                cardButton[i]->canBeClicked = false;
            }
        }
        for(int i = 0;i < 5;i++)
        {
            cheat->number[i]->canBeClicked = false;
        }
        cheatSet();
    }
}
void Adventurer::countMinus()
{
    if(cheatCount == 3)
    {
        cheatCount --;
        for(int i = 0;i < 5;i++)
        {
            cheat->number[i]->canBeClicked = true;
            cheat->ensure->canBeClicked = false;
        }
    }
    if(cheatCount == 2)
    {
        cheatCount --;
        for(int i = 0;i < 5;i++)
        {
            cheat->number[i]->canBeClicked = false;
        }
    }
    if(cheatCount == 1)
    {
        magicSetZero();
    }
}
void Adventurer::cheatSet()
{
    for(int i = 0;i < 6;i++)
    {
        if(paintStructX->gameCharacter[i]->color != paintStructX->gameCharacter[5]->color)
        {
            paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
        }
    }
}
void Adventurer::cheatReset()
{
    ensure->canBeClicked = false;
    for(int i = 0;i < 6;i++)
    {
        if(paintStructX->gameCharacter[i]->color != paintStructX->gameCharacter[5]->color)
        {
            paintStructX->gameCharacter[i]->characterPic->canBeClicked = false;
        }
    }
}
void Adventurer::sendMessageSelf()
{
    for(int i = 0;i < 3;i++)
    {
        if(magicGroup[i]->isClicked)
        {
            informationKind = 200 + i;
        }
    }
    std::vector<int> tempMes;
    if(cancel->isClicked && informationKind < 100)
    {
        if(informationKind == 7)
        {
            tempMes.push_back(-1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        tempMes.push_back(0);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    if(cancel->isClicked && informationKind > 99 && !ensure->canBeClicked)
    {
        tempMes.push_back(-1);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    if(cancel->isClicked && informationKind > 99 && ensure->canBeClicked)
    {
        tempMes.push_back(0);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    switch(informationKind)
    {
        case 200://欺诈响应阶段
        {
            tempMes.push_back(0);
            tempMes.push_back(6);
            for(int i = 0;i < 6;i++)
            {
                if(paintStructX->gameCharacter[i]->characterPic->isClicked)
                {
                    int site = (-i + 5 + paintStructX->yourSite) % 6;
                    tempMes.push_back(site);
                }
            }
            int cardCount = 0;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    cardCount ++;
                }
            }
            tempMes.push_back(cardCount);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    tempMes.push_back(card[i]);
                }
            }
            for(int i = 0;i < 5;i++)
            {
                if(cheat->number[i]->isClicked)
                {
                    tempMes.push_back(i);
                }
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 202://偷天换日响应阶段
        case 201://特殊加工响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(informationKind - 200);
            emit sendMessageSelfSig(tempMes);
            return;

        }
        default:
        {
            sendMessageIn();
        }
    }
}
