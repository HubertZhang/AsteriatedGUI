#include "elementmaster.h"

ElementMaster::ElementMaster(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    magicCount = 0;
    //dialog->init(11);//无
    magicGroup[0] = new PicButton(92,362,559,100,42,false);
    magicGroup[1] = new PicButton(93,465,559,100,42,false);
    magicGroup[2] = new PicButton(94,568,559,100,42,false);
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
void ElementMaster::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void ElementMaster::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
}
void ElementMaster::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->isClicked = true;
}
void ElementMaster::changeSelfMode(int mode)
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
        case 4://元素点燃响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
            }
            break;
        }
        case 5://元素法术响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillTwo(card[i])/10 == 11)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
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
        case 6://月光响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
            }
            break;
        }
    }
}
void ElementMaster::paint(QPaintEvent *event, QPainter *painter)
{
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
void ElementMaster::skillset()
{
    if(paintStructX->gameCharacter[5]->yellow == 3)
    {
        magicGroup[0]->canBeClicked = true;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillTwo(card[i])/10 == 11)
        {
            magicGroup[1]->canBeClicked = true;
            break;
        }
    }
    if(paintStructX->gameCharacter[5]->gem != 0)
    {
        magicGroup[2]->canBeClicked = true;
    }
}
void ElementMaster::skillCancel()
{
    magicCount = 0;
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
void ElementMaster::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void ElementMaster::countPlus()
{
    if(magicCount == 0)
    {
        magicCount++;
        for(int i = 0;i < 6;i++)
        {
            paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
        }
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
            if(cardList->getNature(card[i]) == attribute)
            {
                cardButton[i]->canBeClicked = true;
            }
        }
        return;
    }
    if(magicCount == 1)
    {
        magicCount ++;
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isClicked)
            {
                cardButton[i]->canBeClicked = false;
            }
        }
        return;
    }
}
void ElementMaster::countMinus()
{
    if(magicCount == 2)
    {
        magicCount --;
        for(int i = 0;i < cardNum;i++)
        {
            if(cardButton[i]->isClicked)
            {
                if(cardList->getSkillTwo(card[i])/10 == 11)
                {
                    break;
                }
                else
                {
                    magicSetOne();
                    break;
                }
            }
        }
    }
    if(magicCount == 1)
    {
        magicSetOne();
    }
}
void ElementMaster::sendMessageSelf()
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
        case 200://元素点燃响应阶段
        case 202://月光点燃响应阶段
        {
            tempMes.push_back(1);
            if(informationKind == 202)
            {
                tempMes.push_back(3);
            }
            else
            {
                tempMes.push_back(1);
            }
            for(int j = 0;j < 6;j++)
            {
                if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                {
                    int site = (-j + paintStructX->yourSite + 5) % 6;
                    tempMes.push_back(site);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://元素法术响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            int cardCount = 0;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    cardCount ++;
                }
            }
            for(int j = 0;j < 6;j++)
            {
                if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                {
                    int site = (-j + paintStructX->yourSite + 5) % 6;
                    tempMes.push_back(site);
                    break;
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
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
