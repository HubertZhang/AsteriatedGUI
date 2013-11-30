#include "magicsword.h"

MagicSword::MagicSword(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    magicCount = 0;
    dialog = new NewDialog(windowX);
    dialog->init(9);//修罗连斩,黑暗震颤
    darkMeteor = new PicButton(85,362,559,100,42,false);
    for(int i = 0;i < dialog->skillCount;i++)
    {
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    connect(this,SIGNAL(mouseClick(int,int)),darkMeteor,SLOT(isThisClicked(int,int)));
    //system("pause");
    connect(darkMeteor,SIGNAL(changeClicked()),this,SLOT(magicSetZero()));
    connect(darkMeteor,SIGNAL(notClicked()),this,SLOT(skillClear()));
}
void MagicSword::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(6);
    darkMeteor->isClicked = true;
}
void MagicSword::changeSelfMode(int mode)
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
        case 4://修罗连斩响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getName(card[i]) == fireAttack)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 5://黑暗震颤响应阶段
        {
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            emit resetSignal();
            break;
        }
        case 6://暗影流星响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(countPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(countMinus()));
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
                    }
                }
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
    }
}
void MagicSword::paint(QPaintEvent *event, QPainter *painter)
{
    if(ask)
    {
        dialog->paint(event,painter);
    }
    darkMeteor->paint(event,painter);
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
void MagicSword::setFrame()
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
void MagicSword::skillset()
{
    int count = 0;
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getType(card[i]) == magic)
        {
            count ++;
        }
    }
    if(count > 1 && paintStructX->gameCharacter[5]->activated)
    {
        darkMeteor->canBeClicked = true;
    }
}
void MagicSword::skillCancel()
{
    magicCount = 0;
    ask = false;
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(countPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
    darkMeteor->canBeClicked = false;
    darkMeteor->isClicked = false;
}
void MagicSword::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void MagicSword::countPlus()
{
    if(magicCount == 0)
    {
        magicCount ++;
        return;
    }
    if(magicCount == 1)
    {
        magicCount ++;
        for(int i = 0;i < 6;i++)
        {
            paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
        }
        return;
    }
    if(magicCount == 2)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(cardButton[i]->isClicked)
            {
                cardButton[i]->isClicked = false;
                break;
            }
        }
        return;
    }
}
void MagicSword::countMinus()
{
    for(int i = 0;i < 6;i++)
    {
        paintStructX->gameCharacter[i]->characterPic->canBeClicked = false;
    }
    magicCount --;
}
void MagicSword::selfReset()
{
    system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            changeSelfMode(4 + i);
        }
    }
    dialogReset();
}
void MagicSword::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void MagicSword::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void MagicSword::magicSwordSet()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getType(card[i]) == magic)
        {
            cardButton[i]->canBeClicked = false;
        }
    }
}
