#include "darkkiller.h"

DarkKiller::DarkKiller(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(5);//水影
    waterCount = 0;
    for(int i = 0;i < 1;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
    }
}
void DarkKiller::changeSelfMode(int mode)
{
    for(int i = 0;i < cardNum;i++)
    {
        connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(countPlus()));
        connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
    cancel->canBeClicked = true;
    switch(mode)
    {
        case 4://水影响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == water)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            //system("pause");
            break;
        }
    }
}
void DarkKiller::paint(QPaintEvent *event, QPainter *painter)
{
    if(ask)
    {
        dialog->paint(event,painter);
        cancel->canBeClicked = true;
    }
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
void DarkKiller::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void DarkKiller::setFrame()
{
    ask = true;
}
void DarkKiller::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            changeSelfMode(4 + i);
        }
    }
    dialogReset();
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->isClicked = false;
    }
}*/
void DarkKiller::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void DarkKiller::countPlus()
{
    waterCount ++;
    ensure->canBeClicked = true;
}
void DarkKiller::countMinus()
{
    waterCount --;
    if(waterCount == 0)
    {
        ensure->canBeClicked = false;
    }
}
void DarkKiller::skillCancel()
{
    waterCount = 0;
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(countPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
}
void DarkKiller::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            informationKind = 100 + i;
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
    if(cancel->isClicked && informationKind > 99)
    {
        tempMes.push_back(-1);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    switch(informationKind)
    {
        case 100://水影响应阶段
        {
            int messageCount = 0;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    messageCount ++;
                }
            }
            if(!messageCount)
            {
                tempMes.push_back(informationKind - 100 + 1);
                emit sendMessageSelfSig(tempMes);
                return;
            }
            tempMes.push_back(messageCount);
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
