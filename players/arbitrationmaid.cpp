#include "arbitrationmaid.h"

ArbitrationMaid::ArbitrationMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    //dialog->init(14);//魔弹融合
    magicGroup[0] = new PicButton(103,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(105,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(106,568,559,100,42,false,this);
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
void ArbitrationMaid::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->setChecked(true);
    if(paintStruct->gameCharacter[5]->yellow == 4)
    {
        magicGroup[1]->setCheckable(false);
        magicGroup[2]->setCheckable(false);
        cancel->setCheckable(false);
    }
}
void ArbitrationMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->setChecked(true);
}
void ArbitrationMaid::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->setChecked(true);
}
void ArbitrationMaid::changeSelfMode(int mode)
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
            if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
    }
    cancel->setCheckable(true);
    switch(mode)
    {
        case 4://末日审判响应阶段
        {
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            }
            break;
        }
        case 5://天平(1)响应阶段
        case 6://天平(2)响应阶段
        {
            ensure->setCheckable(true);
            break;
        }
    }
}
//void ArbitrationMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    for(int i = 0;i < 3;i++)
//    {
//        magicGroup[i]->paint(event,painter);
//    }
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    for(int i = 0;i < cardNum;i++)
//    {
//        cardButton[i]->paint(event,painter);
//    }
//}
void ArbitrationMaid::skillset()
{
    if(paintStruct->gameCharacter[5]->yellow != 0)
    {
        magicGroup[0]->setCheckable(true);
    }
    if(paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal != 0)
    {
        magicGroup[1]->setCheckable(true);
        magicGroup[2]->setCheckable(true);
    }
}
void ArbitrationMaid::skillCancel()
{
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
}
void ArbitrationMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void ArbitrationMaid::sendMessageSelf()
{
    for(int i = 0;i < 3;i++)
    {
        if(magicGroup[i]->isChecked())
        {
            informationKind = 200 + i;
        }
    }
    std::vector<int> tempMes;
    if(cancel->isChecked() && informationKind < 100)
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
    if(cancel->isChecked() && informationKind > 99 && !ensure->isCheckable())
    {
        tempMes.push_back(-1);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    if(cancel->isChecked() && informationKind > 99 && ensure->isCheckable())
    {
        tempMes.push_back(0);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    switch(informationKind)
    {
        case 200://末日审判响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            putCharacter(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://天平1响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            discardAll();
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 202://天平2响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(3);
            emit sendMessageSelfSig(tempMes);
            return;

        }
        default:
        {
            sendMessageIn();
        }
    }
}
void ArbitrationMaid::arbitrationEnd()
{
    magicSetZero();
    magicGroup[0]->setChecked(false);
    magicGroup[1]->setCheckable(false);
    magicGroup[2]->setCheckable(false);
    cancel->setCheckable(false);
}
void ArbitrationMaid::discardAll()
{
    for(int i = 0;i < cardNum;i++)
    {
        delete cardButton[i];
    }
    cardNum = 0;
}
