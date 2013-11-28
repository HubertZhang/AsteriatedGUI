#include "arrowmaid.h"

ArrowMaid::ArrowMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(3);//贯穿射击,精准射击
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 2;j++)
        {
            if(i != j)
            {
                connect(dialog->skillGroup[i],SIGNAL(changeClicked()),dialog->skillGroup[j],SLOT(cancelX()));
            }
        }
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
    }
    kiraTrap = new PicButton(62,362,559,100,42,false);
    snipe = new PicButton(64,465,559,100,42,false);
    connect(this,SIGNAL(mouseClick(int,int)),kiraTrap,SLOT(isThisClicked(int,int)));
    connect(this,SIGNAL(mouseClick(int,int)),snipe,SLOT(isThisClicked(int,int)));
    connect(kiraTrap,SIGNAL(changeClicked()),snipe,SLOT(cancelX()));
    connect(snipe,SIGNAL(changeClicked()),kiraTrap,SLOT(cancelX()));
    connect(kiraTrap,SIGNAL(changeClicked()),this,SLOT(kiraTrapRes()));
    connect(snipe,SIGNAL(changeClicked()),this,SLOT(snipeRes()));
    connect(kiraTrap,SIGNAL(notClicked()),this,SLOT(skillClear()));
    connect(snipe,SIGNAL(notClicked()),this,SLOT(skillClear()));
}
void ArrowMaid::changeSelfMode(int mode)
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
        case 6://闪光陷阱响应阶段
        {
            cancel->canBeClicked = false;
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillTwo(card[i]) == 32)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            //disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 4:
        case 5://精准射击响应阶段
        {
            emit resetSignal();
            break;
        }
        case 7://狙击
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
                //disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            }
            break;
        }
    }
}
void ArrowMaid::paint(QPaintEvent *event, QPainter *painter)
{
    if(ask)
    {
        dialog->paint(event,painter);
        cancel->canBeClicked = true;
    }
    kiraTrap->paint(event,painter);
    snipe->paint(event,painter);
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
void ArrowMaid::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void ArrowMaid::setFrame()
{
    ask = true;
}
void ArrowMaid::selfReset()
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
void ArrowMaid::dialogReset()
{
    //system("pause");
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void ArrowMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillTwo(card[i]) == 32)
        {
            kiraTrap->canBeClicked = true;
        }
    }
    if(paintStructX->gameCharacter[5]->gem + paintStructX->gameCharacter[5]->crystal != 0)
    {
        snipe->canBeClicked = true;
    }
}
void ArrowMaid::skillCancel()
{
    snipe->canBeClicked = false;
    kiraTrap->canBeClicked = false;
    snipe->isClicked = false;
    kiraTrap->isClicked = false;
}
void ArrowMaid::kiraTrapRes()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    kiraTrap->isClicked = true;
}
void ArrowMaid::snipeRes()
{
    linkReset();
    skillset();
    changeSelfMode(7);
    snipe->isClicked = true;
}
void ArrowMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
