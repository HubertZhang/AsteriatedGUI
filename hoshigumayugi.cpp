#include "hoshigumayugi.h"

HoshigumaYugi::HoshigumaYugi(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(21);//怒吼,明镜止水,禁断之力,死斗
    provoke = new PicButton(140,362,559,100,42,false);
    for(int i = 0;i < dialog->skillCount;i++)
    {
        for(int j = 0;j < dialog->skillCount;j++)
        {
            if(i != j)
            {
                connect(dialog->skillGroup[i],SIGNAL(changeClicked()),dialog->skillGroup[j],SLOT(cancelX()));
            }
        }
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    connect(this,SIGNAL(mouseClick(int,int)),provoke,SLOT(isThisClicked(int,int)));
    //system("pause");
    connect(provoke,SIGNAL(changeClicked()),this,SLOT(magicSetZero()));
    connect(provoke,SIGNAL(notClicked()),this,SLOT(skillClear()));
}
void HoshigumaYugi::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(6);
    provoke->isClicked = true;
}
void HoshigumaYugi::changeSelfMode(int mode)
{
    cancel->canBeClicked = true;
    switch(mode)
    {
        case 4://怒吼响应阶段
        case 5://明镜止水响应阶段
        case 7://禁断之力响应阶段
        case 8://死斗响应阶段
        {
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            emit resetSignal();
            break;
        }
        case 6://挑衅响应阶段
        {
            cancel->canBeClicked = false;
            clickRivalSet();
            break;
        }
    }
}
void HoshigumaYugi::paint(QPaintEvent *event, QPainter *painter)
{
    if(ask)
    {
        dialog->paint(event,painter);
    }
    provoke->paint(event,painter);
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
void HoshigumaYugi::setFrame()
{
    ask = true;
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->isClicked = false;
    }
}*/
void HoshigumaYugi::skillset()
{
    if(paintStructX->gameCharacter[5]->yellow > 0)
    {
        provoke->canBeClicked = true;
    }
}
void HoshigumaYugi::skillCancel()
{
    ask = false;
    dialog->label->hide();
    provoke->canBeClicked = false;
    provoke->isClicked = false;
}
void HoshigumaYugi::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void HoshigumaYugi::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            if(i < 2)
            {
                changeSelfMode(4 + i);
            }
            else
            {
                changeSelfMode(5 + i);
            }
        }
    }
    dialogReset();
}
void HoshigumaYugi::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void HoshigumaYugi::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void HoshigumaYugi::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            informationKind = 100 + i;
        }
    }
    if(provoke->isClicked)
    {
        informationKind = 200;
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
        case 100://怒吼响应阶段
        case 101://明镜止水响应阶段
        case 103://死斗响应阶段
        {
            if(informationKind > 101)
            {
                tempMes.push_back(informationKind - 98);
            }
            else
            {
                tempMes.push_back(informationKind - 99);
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 102://禁断之力
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
            tempMes.push_back(cardNum);
            for(int i = 0;i < cardNum;i++)
            {
                tempMes.push_back(card[i]);
            }
            discardAll();
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://挑衅响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(3);
            putCharacter(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
void HoshigumaYugi::discardAll()
{
    for(int i = 0;i < cardNum;i++)
    {
        delete cardButton[i];
    }
    cardNum = 0;
}
