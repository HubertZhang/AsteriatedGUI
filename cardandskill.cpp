#include "cardandskill.h"
#include <QString>
#include <QLabel>
#include <cstdlib>
#include <iostream>
using namespace std;
CardAndSkill::CardAndSkill(PaintStruct* paintStruct ,QWidget *parent) : QWidget(parent)
{
    setGeometry(0,0,1366,768);
    informationKind = 0;
    cancelClick = false;
    frame = false;
    this->paintStruct = paintStruct;
    cardNum = 0;
    windowX = parent;
    paintMode = 0;
    cardList = new CardList();
    ensure = new PicButton(32,775,559,100,42,false,this);
    cancel = new PicButton(33,878,559,100,42,false,this);
    frameLabel = new FrameLabel(windowX);
    connect(ensure,SIGNAL(beChecked()),this,SLOT(sendMessageCardAndSkill()));
    connect(cancel,SIGNAL(beChecked()),this,SLOT(sendMessageCardAndSkill()));
    connect(this,SIGNAL(resetSignal()),this,SLOT(reset()));
    connect(ensure,SIGNAL(beChecked()),this,SLOT(cardDis()));
    connect(ensure,SIGNAL(beChecked()),this,SLOT(reset()));
    connect(cancel,SIGNAL(beChecked()),this,SLOT(reset()));
    connect(cancel,SIGNAL(beChecked()),this,SLOT(dialogReset()));
    connect(this,SIGNAL(skillSetSig()),this,SLOT(skillset()));
    for(int j = 0;j < 6;j++)
    {
        paintStruct->gameCharacter[j]->characterPic->setCheckable(false);
        paintStruct->gameCharacter[j]->characterPic->setChecked(false);
    }
    cancel->setCheckable(false);
    ensure->setCheckable(false);
    cancel->setChecked(false);
    ensure->setChecked(false);
    //system("pause");
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(false);
        cardButton[i]->setChecked(false);

    }
    show();
    //connect(ensure,SIGNAL(beChecked()),this,SLOT(paintSignal()));
}
//void CardAndSkill::paint(QPaintEvent* event, QPainter* painter)
//{
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    for(int i = 0;i < cardNum;i++)
//    {
//        cardButton[i]->paint(event,painter);
//    }
//    if(frame)
//    {
//        frameLabel->paint(event,painter);
//    }
//}
void CardAndSkill::linkReset()
{
    if(frame)
    {
        //system("pause");
        frameLabel->labelOne->hide();
        frameLabel->labelTwo->hide();
        frame = false;
    }
    skillCancel();
    for(int j = 0;j < 6;j++)
    {
        paintStruct->gameCharacter[j]->characterPic->setCheckable(false);
        paintStruct->gameCharacter[j]->characterPic->setChecked(false);
    }
    cancel->setCheckable(false);
    ensure->setCheckable(false);
    cancel->setChecked(false);
    ensure->setChecked(false);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(false);
        cardButton[i]->setChecked(false);
        disconnect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        disconnect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableFalse()));
        disconnect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        for(int j = 0;j < cardNum;j++)
        {
            if(i != j)
            {
                disconnect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
    for(int i = 0;i < cardNum;i ++)
    {
        for(int j = 0;j < 6;j++)
        {
            disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
            disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
        }
    }
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(beChecked()),this,SLOT(discardPlus()));
        disconnect(cardButton[i],SIGNAL(unChecked()),this,SLOT(discardMinus()));
    }
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
                paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
            }
            for(int i = 0;i < cardNum;i++)
            {
                cardButton[i]->setCheckable(false);
            }
            break;
        }
        case 1://应战时
        {
            //information[0]:是否可以应战
            //information[1]:卡片序号
            //information[2]:攻击人
            cancel->setCheckable(true);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
            }
            for(int i = 0;i < cardNum;i ++)
            {
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
                    }
                }
                for(int j = 0;j < 6;j++)
                {
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
                }
                if(!information[0])
                {
                    if(cardList->getName(card[i]) != holyLight)
                    {
                        cardButton[i]->setCheckable(false);
                    }
                    else
                    {
                        cardButton[i]->setCheckable(true);
                        connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                        connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                    }
                }
                else
                {
                    if(cardList->getName(card[i]) == cardList->getName(information[1]) || cardList->getName(card[i]) == darkAttack)
                    {
                        cardButton[i]->setCheckable(true);
                        connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableFalse()));
                        connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                        for(int j = 0;j < 6;j ++)
                        {
                            for(int k = 0;k < 6;k++)
                            {
                                if(j != k)
                                {
                                    connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[k]->characterPic,SLOT(setCheckedFalse()));
                                }
                            }
                            if(paintStruct->gameCharacter[j]->color != paintStruct->gameCharacter[5]->color && j!= information[2])
                            {
                                connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                                connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                                connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                                connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                            }
                        }
                    }
                    else if(cardList->getName(card[i]) == holyLight)
                    {
                        cardButton[i]->setCheckable(true);
                        connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                        //TODO
                        for(int j = 0;j < 6;j ++)
                        {
                            connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                        }
                        connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                    }
                    else
                    {
                        cardButton[i]->setCheckable(false);
                    }
                }
            }
            break;
        }
        case 2://回合内
        {
            if(paintStruct->gameCharacter[5]->characterNum == 14)
            {
                if(paintStruct->gameCharacter[5]->yellow == 4)
                {
                    arbitrationEnd();
                    return;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
                    }
                }
                for(int j = 0;j < 6;j++)
                {
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
                }
                if(cardList->getName(card[i])== holyLight)
                {
                    cardButton[i]->setCheckable(false);
                }
                else
                {
                    cardButton[i]->setCheckable(true);
                    if(cardList->getType(card[i]) == attack)
                    {
                        connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableFalse()));
                        connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                        for(int j = 0;j < 6;j ++)
                        {
                            for(int k = 0;k < 6;k++)
                            {
                                if(j != k)
                                {
                                    connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[k]->characterPic,SLOT(setCheckedFalse()));
                                }
                            }
                            if(paintStruct->gameCharacter[j]->color != paintStruct->gameCharacter[5]->color && !(paintStruct->gameCharacter[j]->characterNum == 5 && paintStruct->gameCharacter[j]->activated))
                            {
                                connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                                connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                                connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                                connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
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
                                connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableFalse()));
                                connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                                for(int j = 0;j < 6;j ++)
                                {
                                    for(int k = 0;k < 6;k++)
                                    {
                                        if(j != k)
                                        {
                                            connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[k]->characterPic,SLOT(setCheckedFalse()));
                                        }
                                    }
                                    bool notfindmagic = true;
                                    int magic = cardList->getName(card[i]);
                                    for(int k = 0;k < paintStruct->gameCharacter[j]->statusNum;k++)
                                    {
                                        if(cardList->getName(paintStruct->gameCharacter[j]->status[k]) == magic)
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
                                        connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                                        connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                                        connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                                        connect(paintStruct->gameCharacter[j]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                                    }
                                }
                                break;
                            }
                            case missile:
                            {
                                if(paintStruct->gameCharacter[5]->characterNum == 8)
                                {
                                    int siteCount = 0;
                                    int left = 0;
                                    int right = 0;
                                    int k = 0;
                                    while(siteCount != 3)
                                    {
                                        if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[k]->color)
                                        {
                                            if(siteCount == 0)
                                            {
                                                left = k;
                                            }
                                            if(siteCount == 2)
                                            {
                                                right = k;
                                            }
                                            siteCount ++;
                                        }
                                        k++;
                                    }
                                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[left]->characterPic,SLOT(setCheckableTrue()));
                                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[left]->characterPic,SLOT(setCheckableFalse()));
                                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[right]->characterPic,SLOT(setCheckableTrue()));
                                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[right]->characterPic,SLOT(setCheckableFalse()));
                                    break;
                                }
                                connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                                connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
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
                cancel->setCheckable(true);
            }
            if(information[1])
            {
                cancel->setCheckable(true);
            }
            else
            {
                cancel->setCheckable(false);
            }
            frame = true;
            frameLabel->labelOne->setText(QString::fromUtf8("请弃掉一张牌"));
            frameLabel->labelTwo->setText("");
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
                    }
                }
            }
            if(information[0])//法术
            {
                for(int i = 0;i < cardNum;i++)
                {
                    if(cardList->getType(card[i]) == magic)
                    {
                        cardButton[i]->setCheckable(true);
                    }
                    else
                    {
                        cardButton[i]->setCheckable(false);
                    }
                }
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    cardButton[i]->setCheckable(true);
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
            cardButton[i] = new CardButton(card[i],364 + (99 + xOffset) * i,611,windowX);
        }
        else
        {
            xOffset = ((102 * 6) - 99)/(cardNum - 1);
            cardButton[i] = new CardButton(card[i],364 + (99 + xOffset) * i,611,windowX);
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
//void CardAndSkill::cardClicked(int x, int y)
//{
//    if(x > 364 && x < 976)
//    {
//        if(y > 611 && y < 754)
//        {
//            if(cardNum < 7)
//            {
//                int i = ((x - 364)/102);
//                if(i > cardNum - 1)
//                {
//                    return;
//                }
//                if(!cardButton[i]->isConnect)
//                {
//                    connect(this,SIGNAL(isChecked()(int,int)),cardButton[i],SLOT(isThisChecked()(int,int)));
//                    cardButton[i]->isConnect = true;
//                }
//                emit isChecked()(x,y);
//            }
//            else
//            {
//                if(x > (976 - 99))
//                {
//                    int x = cardButton[cardNum - 1]->xp + 50;
//                    int y = cardButton[cardNum - 1]->yp + 50;
//                    cardButton[cardNum - 1]->isThisChecked()(x,y);
//                }
//                else
//                {
//                    int i = (x - 364)/(((102 * 6) - 99)/(cardNum - 1));
//                    int x = cardButton[i]->xp + 50;
//                    int y = cardButton[i]->yp + 50;
//                    cardButton[i]->isThisChecked()(x,y);
//                }
//            }
//        }
//    }
//}
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
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
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
        if(cardButton[i]->isChecked())
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
        if(cardButton[i]->isChecked())
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
//void CardAndSkill::send(int x, int y)
//{
//    emit mouseClick(x,y);
//}
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
void CardAndSkill::discard(int count)
{
    discardCount = 0;
    allCount = count;
    for(int i = 0;i < cardNum;i++)
    {
        connect(cardButton[i],SIGNAL(beChecked()),this,SLOT(discardPlus()));
        connect(cardButton[i],SIGNAL(unChecked()),this,SLOT(discardMinus()));
        cardButton[i]->setCheckable(true);
    }
}
void CardAndSkill::discardPlus()
{
    discardCount ++;
    if(discardCount == allCount)
    {
        ensure->setCheckable(true);
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isChecked())
            {
                cardButton[i]->setCheckable(false);
            }
        }
    }

}
void CardAndSkill::discardMinus()
{
    discardCount --;
    ensure->setCheckable(false);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(true);
    }
}
void CardAndSkill::append(int appKind)
{
    int info[3] = {0,0,0};
    informationKind = 7;
    changePaintMode(2,info);
    cancel->setCheckable(true);
    if(appKind == 1)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getType(card[i]) == attack)
            {
                cardButton[i]->setCheckable(false);
            }
        }
        skillset();
    }
    else if(!appKind)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getType(card[i]) == magic && cardList->getName(card[i]) != holyLight)
            {
                cardButton[i]->setCheckable(false);
            }
        }
        skillCancel();//Special Adventurer
    }
}
void CardAndSkill::magicSwordSet()
{

}
void CardAndSkill::missileAttack()
{
    cancel->setCheckable(true);
    informationKind = 20;
    if(paintStruct->gameCharacter[5]->characterNum == 8)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getName(card[i]) == missile || cardList->getNature(card[i]) == fire || cardList->getNature(card[i]) == ground ||cardList->getName(card[i]) == holyLight)
            {
                cardButton[i]->setCheckable(true);
                connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
                    }
                }
            }
        }
        return;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getName(card[i]) == missile || cardList->getName(card[i]) == holyLight)
        {
            cardButton[i]->setCheckable(true);
            connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
            connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));            
            for(int j = 0;j < cardNum;j++)
            {
                if(i != j)
                {
                    connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
                }
            }
        }
    }
}
void CardAndSkill::priestAct()
{

}
void CardAndSkill::sendMessageIn()
{
    //system("pause");
    std::vector<int> tempMes;
    switch(informationKind)
    {
        case 7:
        {
            if(cancel->isChecked())
            {
                tempMes.push_back(-1);
                emit sendMessageInSig(tempMes);
                return;
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isChecked())
                {
                    if(paintStruct->gameCharacter[5]->characterNum == 8 && cardList->getName(card[i]) == missile)
                    {
                        tempMes.push_back(1);
                        tempMes.push_back(2);
                        for(int j = 0;j < 6;j++)
                        {
                            if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                            {
                                int site = (-j + paintStruct->yourSite + 5) % 6;
                                tempMes.push_back(site);
                                tempMes.push_back(card[i]);
                                emit sendMessageInSig(tempMes);
                                return;
                            }
                        }
                    }
                    if(cardList->getType(card[i]) == attack)
                    {
                        //system("pause");
                        tempMes.push_back(0);
                    }
                    else
                    {
                        tempMes.push_back(1);
                        tempMes.push_back(0);
                    }
                    bool missileFind = false;
                    for(int j = 0;j < 6;j++)
                    {
                        if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                        {
                            missileFind = true;
                            //system("pause");
                            int site = ((-j + 5 + paintStruct->yourSite) % 6);
                            tempMes.push_back(site);
                            lastAttackSet(j);
                        }
                    }
                    if(!missileFind)
                    {
                        tempMes.push_back(7);
                    }
                    tempMes.push_back(card[i]);
                    emit sendMessageInSig(tempMes);
                    return;
                }
            }
            break;
        }
        case 11:
        {
            if(cancel->isChecked())
            {
                tempMes.push_back(0);
                emit sendMessageInSig(tempMes);
                return;
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isChecked())
                {
                    if(cardList->getName(card[i]) == holyLight)
                    {
                        tempMes.push_back(2);
                        tempMes.push_back(card[i]);
                        emit sendMessageInSig(tempMes);
                        return;
                    }
                    else
                    {
                        //system("pause");
                        tempMes.push_back(1);
                        for(int j = 0;j < 6;j++)
                        {
                            if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                            {
                                int site = ((-j + 5 + paintStruct->yourSite) % 6);
                                tempMes.push_back(site);
                                break;
                            }
                        }
                        tempMes.push_back(card[i]);
                        emit sendMessageInSig(tempMes);
                        return;
                    }
                }
            }
            break;
        }
    }
}
void CardAndSkill::sendMessageDis()
{
    std::vector<int> tempMes;
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            tempMes.push_back(card[i]);
        }
    }
    emit sendMessageDisSig(tempMes);
    return;
}

void CardAndSkill::sendMessageSelf()
{

}
void CardAndSkill::sendMessageCardAndSkill()
{
    if(informationKind == 17)
    {
        sendMessageDis();
    }
    else if(informationKind == 20)
    {
        sendMessageMis();
    }
    else if(informationKind == 21)
    {
        sendMessageIce();
    }
    else if(informationKind == 14)
    {
        sendMessageOne();
    }
    else
    {
        sendMessageSelf();
    }
}
void CardAndSkill::sendMessageIce()
{
    std::vector <int> tempMes;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            int site = (-i + paintStruct->yourSite + 5) % 6;
            tempMes.push_back(site);
            emit sendMessageIceSig(tempMes);
            return;
        }
    }
}
void CardAndSkill::sendMessageMis()
{
    std::vector <int> tempMes;
    if(cancel->isChecked())
    {
        tempMes.push_back(0);
        emit sendMessageMisSig(tempMes);
        return;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            if(cardList->getName(card[i]) == holyLight)
            {
                tempMes.push_back(2);
            }
            else
            {
                tempMes.push_back(1);
            }
            tempMes.push_back(card[i]);
            emit sendMessageMisSig(tempMes);
            return;
        }
    }

}
void CardAndSkill::sendMessageOne()
{
    std::vector <int> tempMes;
    if(cancel->isChecked())
    {
        tempMes.push_back(-1);
        emit sendMessageOneSig(tempMes);
        return;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            tempMes.push_back(card[i]);
            emit sendMessageOneSig(tempMes);
            return;
        }
    }

}
void CardAndSkill::putCard(std::vector<int> &m)
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            m.push_back(card[i]);
        }
    }
}
void CardAndSkill::putCharacter(std::vector<int> &m)
{
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            int site = (-i + 5 + paintStruct->yourSite) % 6;
            m.push_back(site);
        }
    }
}
void CardAndSkill::putCardCount(std::vector<int> &m)
{
    int cardCount = 0;
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            cardCount ++;
        }
    }
    m.push_back(cardCount);
}
void CardAndSkill::putCharacterCount(std::vector<int> &m)
{
    int characterCount = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            characterCount ++;
        }
    }
    m.push_back(characterCount);
}
void CardAndSkill::icePoetry()
{

}
void CardAndSkill::arbitrationEnd()
{

}
void CardAndSkill::lastAttackSet(int m)
{

}
void CardAndSkill::clickRivalSet()
{
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
        if(paintStruct->gameCharacter[i]->color != paintStruct->gameCharacter[5]->color)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
            connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        }
    }
}
void CardAndSkill::clickAllSet()
{
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
        paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
}
void CardAndSkill::singleToEnsure()
{
    for(int i = 0;i < 6;i++)
    {
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
}
void CardAndSkill::YuukaOne()
{

}
void CardAndSkill::YuukaTwo()
{

}
void CardAndSkill::damageSet(int x)
{

}
void CardAndSkill::cardSingleSet(int attribute)
{
    for(int i = 0;i < cardNum;i++)
    {
        for(int j = 0;j < cardNum;j++)
        {
            if(i != j)
            {
                connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
            }
        }
    }
    if(attribute > 10)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getSkillOne(card[i]) == attribute||cardList->getSkillTwo(card[i]) == attribute)
            {
                cardButton[i]->setCheckable(true);
            }
        }
    }
    else if(attribute < 7 && attribute != -1)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getNature(card[i]) == attribute)
            {
                cardButton[i]->setCheckable(true);
            }
        }
    }
    else
    {
        if(attribute == 8)//attack
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == attack)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
        }
        if(attribute == 9)//magic
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
        }
    }
    if(attribute == -1)
    {
        for(int i = 0;i < cardNum;i++)
        {
            cardButton[i]->setCheckable(true);
        }
    }
}
void CardAndSkill::cardSingle()
{
    for(int i = 0;i < cardNum;i++)
    {
        connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
}
void CardAndSkill::allReset()
{
    for(int i = 0;i < 6;i++)
    {
        paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
        paintStruct->gameCharacter[i]->characterPic->setChecked(false);
    }
}
void CardAndSkill::cardResetOne()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(!cardButton[i]->isChecked())
        {
            cardButton[i]->setCheckable(false);
        }
    }
}
void CardAndSkill::cardSetOne()
{
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(true);
    }
}
void CardAndSkill::clickFriendSet()
{
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
        if(paintStruct->gameCharacter[i]->color == paintStruct->gameCharacter[5]->color && i < 5)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
            connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        }
    }
}
bool CardAndSkill::redWhiteLink()
{
    return false;
}
void CardAndSkill::lifeLinkOver()
{

}
void CardAndSkill::clickRedWhiteSet()
{

}
void CardAndSkill::butterflyTokenAdd(int tokenX[])
{

}
void CardAndSkill::characterDisconnect()
{
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
}
