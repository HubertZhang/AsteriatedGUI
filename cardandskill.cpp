#include "cardandskill.h"
#include <QString>
#include <QLabel>
#include <cstdlib>
#include <iostream>
using namespace std;
CardAndSkill::CardAndSkill(PaintStruct* paintStruct ,QWidget *parent) :
    QWidget(parent)
{
    cancelClick = false;
    frame = false;
    paintStructX = paintStruct;
    cardNum = 0;
    windowX = parent;
    paintMode = 0;
    cardList = new CardList();
    ensure = new PicButton(32,775,559,100,42,false);
    cancel = new PicButton(33,878,559,100,42,false);
    frameLabel = new FrameLabel(windowX);
    connect(this,SIGNAL(resetSignal()),this,SLOT(reset()));
    connect(ensure,SIGNAL(changeClicked()),this,SLOT(cardDis()));
    connect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
    connect(cancel,SIGNAL(changeClicked()),this,SLOT(reset()));
    connect(cancel,SIGNAL(changeClicked()),this,SLOT(dialogReset()));
    connect(this,SIGNAL(skillSetSig()),this,SLOT(skillset()));
    for(int j = 0;j < 6;j++)
    {
        paintStructX->gameCharacter[j]->characterPic->canBeClicked = false;
        paintStructX->gameCharacter[j]->characterPic->isClicked = false;
    }
    cancel->canBeClicked = false;
    ensure->canBeClicked = false;
    cancel->isClicked = false;
    ensure->isClicked = false;
    //system("pause");
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->canBeClicked = false;
        cardButton[i]->isClicked = false;

    }
    //connect(ensure,SIGNAL(changeClicked()),this,SLOT(paintSignal()));
}
void CardAndSkill::paint(QPaintEvent* event, QPainter* painter)
{
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
    if(frame)
    {
        frameLabel->paint(event,painter);
    }
}
void CardAndSkill::linkReset()
{
    //system("pause");
    if(frame)
    {
        frame = false;
        frameLabel->reset();
    }
    skillCancel();
    for(int j = 0;j < 6;j++)
    {
        paintStructX->gameCharacter[j]->characterPic->canBeClicked = false;
        paintStructX->gameCharacter[j]->characterPic->isClicked = false;
    }
    cancel->canBeClicked = false;
    ensure->canBeClicked = false;
    cancel->isClicked = false;
    ensure->isClicked = false;
    //system("pause");
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->canBeClicked = false;
        cardButton[i]->isClicked = false;
        disconnect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        disconnect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < cardNum;j++)
        {
            if(i != j)
            {
                disconnect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
    }
    for(int i = 0;i < cardNum;i ++)
    {
        for(int j = 0;j < 6;j++)
        {
            disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
            disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
        }
    }
    //system("pause");
}
void CardAndSkill::changePaintMode(int mode,int information[3])
{
    if(mode == paintMode)
    {
        return;
    }
    switch(mode)
    {
        case 0://回合外
        {
            for(int i = 0;i < 6;i ++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = false;
            }
            for(int i = 0;i < cardNum;i++)
            {
                cardButton[i]->canBeClicked = false;
            }
            break;
        }
        case 1://应战时
        {
            //information[0]:是否可以应战
            //information[1]:卡片序号
            //information[2]:攻击人
            cancel->canBeClicked = true;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = false;
            }
            for(int i = 0;i < cardNum;i ++)
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
                    connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
                }
                if(!information[0])
                {
                    if(cardList->getName(card[i]) != holyLight)
                    {
                        cardButton[i]->canBeClicked = false;
                    }
                    else
                    {
                        cardButton[i]->canBeClicked = true;
                        connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                    }
                }
                else
                {
                    if(cardList->getName(card[i]) == cardList->getName(information[1]))
                    {
                        cardButton[i]->canBeClicked = true;
                        connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(cancelClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                        for(int j = 0;j < 6;j ++)
                        {
                            for(int k = 0;k < 6;k++)
                            {
                                if(j != k)
                                {
                                    connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[k]->characterPic,SLOT(cancelX()));
                                }
                            }
                            if(paintStructX->gameCharacter[j]->color != paintStructX->gameCharacter[5]->color && j!= information[2])
                            {
                                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                                connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                                connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                            }
                        }
                    }
                    else if(cardList->getName(card[i]) == holyLight)
                    {
                        cardButton[i]->canBeClicked = true;
                        connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                        for(int j = 0;j < 6;j ++)
                        {
                            connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                        }
                        connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                    }
                    else
                    {
                        cardButton[i]->canBeClicked = false;
                    }
                }
            }
            break;
        }
        case 2://回合内
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
                    connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
                }
                if(cardList->getName(card[i])== holyLight)
                {
                    cardButton[i]->canBeClicked = false;
                }
                else
                {
                    cardButton[i]->canBeClicked = true;
                    if(cardList->getType(card[i]) == attack)
                    {
                        connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(cancelClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                        for(int j = 0;j < 6;j ++)
                        {
                            for(int k = 0;k < 6;k++)
                            {
                                if(j != k)
                                {
                                    connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[k]->characterPic,SLOT(cancelX()));
                                }
                            }
                            if(paintStructX->gameCharacter[j]->color != paintStructX->gameCharacter[5]->color)
                            {
                                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                                connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                                connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                            }
                        }
                    }
                    else
                    {
                        switch(cardList->getName(card[i]))
                        {
                            case weak:
                            case shield:
                            case poison:
                            {
                                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(cancelClick()));
                                connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                                for(int j = 0;j < 6;j ++)
                                {
                                    for(int k = 0;k < 6;k++)
                                    {
                                        if(j != k)
                                        {
                                            connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[k]->characterPic,SLOT(cancelX()));
                                        }
                                    }
                                    bool notfindmagic = true;
                                    int magic = cardList->getName(card[i]);
                                    for(int k = 0;k < paintStructX->gameCharacter[j]->statusNum;k++)
                                    {
                                        if(cardList->getName(paintStructX->gameCharacter[j]->status[k]) == magic)
                                        {
                                            notfindmagic = false;
                                        }
                                    }
                                    if(magic == poison)
                                    {
                                        notfindmagic = true;
                                    }
                                    if(notfindmagic)
                                    {
                                        connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                                        connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                                        connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                                        connect(paintStructX->gameCharacter[j]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                                    }
                                }
                                break;
                            }
                            case missile:
                            {
                                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(cancelClick()));
                                break;
                            }
                        }
                    }
                }
            }
            //system("pause");
            emit skillSetSig();
            break;
        }
        case 3://请弃掉一张牌
        {
            if(cardNum == 0)
            {
                cancel->canBeClicked = true;
            }
            if(information[1])
            {
                cancel->canBeClicked = true;
            }
            frame = true;
            frameLabel->labelOne->setText(QString::fromUtf8("请弃掉一张牌"));
            frameLabel->labelTwo->setText("");
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        connect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
                    }
                }
            }
            if(information[0])//法术
            {
                for(int i = 0;i < cardNum;i++)
                {
                    if(cardList->getType(card[i]) == magic)
                    {
                        cardButton[i]->canBeClicked = true;
                    }
                    else
                    {
                        cardButton[i]->canBeClicked = false;
                    }
                }
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            break;
        }
    }
}
void CardAndSkill::buttonFixed()
{
    int xOffset = 3;
    int cardUsed = 0;
    int cardTem[15];
    for(int i = 0;i < 15;i++)
    {
        cardTem[i] = 0;
    }
    for(int i = 0;i < cardNum;i ++)
    {
        if(card[i] == -1)
        {
            cardUsed++;
        }
        else
        {
            cardTem[i - cardUsed] = card[i];
        }
    }
    cardNum -= cardUsed;
    for(int i = 0;i < cardNum;i++)
    {
        card[i] = cardTem[i];
    }
    for(int i = 0;i < cardNum;i ++)
    {
        if(cardNum < 7)
        {
            cardButton[i] = new CardButton(48,364 + (99 + xOffset) * i,611,99,143,false,card[i],windowX);
        }
        else
        {
            xOffset = ((102 * 6) - 99)/(cardNum - 1);
            cardButton[i] = new CardButton(48,364 + xOffset * i,611,99,143,false,card[i],windowX);
        }
    }
}
void CardAndSkill::destroyCard()
{
    for(int i = 0;i < cardNum;i++)
    {
        delete cardButton[i];
    }
}
void CardAndSkill::cardClicked(int x, int y)
{
    if(x > 364 && x < 976)
    {
        if(y > 611 && y < 754)
        {
            if(cardNum < 7)
            {
                int i = ((x - 364)/102);
                if(i > cardNum - 1)
                {
                    return;
                }
                if(!cardButton[i]->isConnect)
                {
                    connect(this,SIGNAL(isClicked(int,int)),cardButton[i],SLOT(isThisClicked(int,int)));
                    cardButton[i]->isConnect = true;
                }
                emit isClicked(x,y);
            }
            else
            {
                if(x > (976 - 99) && !cardButton[cardNum - 1]->isConnect)
                {
                    connect(this,SIGNAL(isClicked(int,int)),cardButton[cardNum - 1],SLOT(isThisClicked(int,int)));
                    cardButton[cardNum - 1]->isConnect = true;
                }
                else
                {
                    int i = (x - 99 - 364)/(((102 * 6) - 99)/(cardNum - 1));
                    if(!cardButton[i]->isConnect)
                    {
                        connect(this,SIGNAL(isClicked(int,int)),cardButton[i],SLOT(isThisClicked(int,int)));
                    }
                }
                emit isClicked(x,y);
            }
        }
    }
}
/*void CardAndSkill::paintSignal()
{
    int info[15];
    for(int i = 0;i < 15;i++)
    {
        info[i] = 0;
    }
    info[0] = 10;
    int target = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStructX->gameCharacter[i]->characterPic->isClicked)
        {
            target ++;
            info[3 + target] = i;
        }
    }
    info[1] = 5;
    info[2] = target;
    int cardUse = 0;
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isClicked)
        {
            cardUse ++;
            info[3 + target + cardUse] = card[i];
            card[i] = -1;
        }
    }
    info[3] = cardUse;
    info[14] = -1;
    destroyCard();
    buttonFixed();
    emit paintAnime(info);
}*/
void CardAndSkill::cardDis()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isClicked)
        {
            card[i] = -1;
        }
    }
    destroyCard();
    buttonFixed();
}
void CardAndSkill::reset()
{
    linkReset();
}
void CardAndSkill::setFrame()
{

}
void CardAndSkill::dialogSet(bool canX[])
{

}
void CardAndSkill::send(int x, int y)
{
    emit mouseClick(x,y);
}
void CardAndSkill::selfReset()
{

}
void CardAndSkill::skillReset()
{

}
void CardAndSkill::changeSelfMode(int mode)
{

}
void CardAndSkill::dialogReset()
{

}
void CardAndSkill::skillset()
{

}
void CardAndSkill::skillCancel()
{

}
void CardAndSkill::setResPara(int para)
{

}
