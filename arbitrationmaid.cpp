#include "arbitrationmaid.h"

ArbitrationMaid::ArbitrationMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    //dialog->init(14);//魔弹融合
    magicGroup[0] = new PicButton(103,362,559,100,42,false);
    magicGroup[1] = new PicButton(105,465,559,100,42,false);
    magicGroup[2] = new PicButton(106,568,559,100,42,false);
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
    magicGroup[0]->isClicked = true;
}
void ArbitrationMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
}
void ArbitrationMaid::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->isClicked = true;
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
        case 4://末日审判响应阶段
        {
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
            }
            break;
        }
        case 5://天平(1)响应阶段
        case 6://天平(2)响应阶段
        {
            ensure->canBeClicked = true;
            break;
        }
    }
}
void ArbitrationMaid::paint(QPaintEvent *event, QPainter *painter)
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
void ArbitrationMaid::skillset()
{
    if(paintStructX->gameCharacter[5]->yellow != 0)
    {
        magicGroup[0]->canBeClicked = true;
    }
    if(paintStructX->gameCharacter[5]->gem + paintStructX->gameCharacter[5]->crystal != 0)
    {
        magicGroup[1]->canBeClicked = true;
        magicGroup[2]->canBeClicked = true;
    }
}
void ArbitrationMaid::skillCancel()
{
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
}
void ArbitrationMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
