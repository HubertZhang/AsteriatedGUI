#include "angel.h"
#include <QString>

Angel::Angel(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    reminiscence = false;
    ask = false;
    blessCount = 0;
    dialog = new NewDialog(windowX);
    windClear = new NewDialog(windowX);
    dialog->init(7);//天使之歌,神之庇护
    windClear->init(101);
    magicGroup[0] = new PicButton(75,362,559,100,42,false);
    magicGroup[1] = new PicButton(76,465,559,100,42,false);
    magicGroup[2] = new PicButton(77,568,559,100,42,false);
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
void Angel::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void Angel::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
}
void Angel::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->isClicked = true;
}
void Angel::changeSelfMode(int mode)
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
        case 4://风之洁净响应阶段
        {
            cancel->canBeClicked = false;
            reminiscence = true;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == wind)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int j = 0;j < 6;j++)
            {
                if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                {
                    disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                    disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                }
                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(reminiscenceSet()));
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(reminiscenceReset()));
                disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            }
            break;
        }
        case 5://天使祝福响应阶段
        {
            cancel->canBeClicked = false;
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == water)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
            connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                    connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
               }
            }
            //disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 6://天使之墙响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillTwo(card[i]) == 71)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    bool shieldExist = false;
                    for(int k = 0;k < paintStructX->gameCharacter[j]->statusNum;k++)
                    {
                        if(cardList->getName(paintStructX->gameCharacter[j]->status[k]) == shield || cardList->getSkillTwo(paintStructX->gameCharacter[j]->status[k] == 71))
                        {
                            shieldExist = true;
                        }
                    }
                    if(!shieldExist)
                    {
                        connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            break;
        }
        case 7://天使之歌响应阶段
        {
        //  cancel->canBeClicked = false;
            reminiscence = true;
            for(int j = 0;j < 6;j++)
            {
                paintStructX->gameCharacter[j]->characterPic->canBeClicked = true;
                if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                {
                    disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                    disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                }
                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(reminiscenceSet()));
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(reminiscenceReset()));
                disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            }
            break;
        }
        case 8:
        {
                
        }
    }
}
void Angel::paint(QPaintEvent *event, QPainter *painter)
{
    if(reminiscence)
    {
        windClear->paint(event,painter);
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
void PureMaid::setFrame()
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
void PureMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillOne(card[i]) == 61)
        {
            magicGroup[0]->canBeClicked = true;
        }
        if(cardList->getSkillOne(card[i]) == 62)
        {
            magicGroup[1]->canBeClicked = true;
        }
    }
    if(paintStructX->gameCharacter[5]->gem + paintStructX->gameCharacter[5]->crystal != 0)
    {
        magicGroup[2]->canBeClicked = true;
    }
}
void PureMaid::skillCancel()
{
    pureLightCount = 0;
    frame = false;
    pureCureCount = 0;
    //pureCureFrame->reset();
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
    for(int i = 0;i < 6;i++)
    {
        disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(pureCurePlus()));
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
}
void PureMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void Angel::countPlus()
{
    ensure->canBeClicked = true;
    if(blessCount < 2)
    {
        blessCount ++;
    }
    else
    {
        for(int i = 0;i < 6;i++)
        {
            if(paintStructX->gameCharacter[i]->characterPic->isClicked)
            {
                paintStructX->gameCharacter[i]->characterPic->isClicked = false;
                break;
            }
        }
    }
}
void Angel::countMinus()
{
    blessCount --;
    if(blessCount == 0)
    {
        ensure->canBeClicked = false;
    }
}
void PureMaid::pureCurePlus()
{
    pureCureCount ++;
    ensure->isClicked = false;
    ensure->canBeClicked = false;
    for(int i = 0;i < 6;i++)
    {
        paintStructX->gameCharacter[i]->characterPic->isClicked = false;
    }
    if(pureCureCount == 3)
    {
        //system("pause");
        linkReset();
        pureCureFrame->reset();
        disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
    }
}

void SealMaid::reminiscenceReset()
{
    for(int i = 0;i < 10;i++)
    {
        sealBreak->skillGroup[i]->canBeClicked = false;
    }
    ensure->canBeClicked = false;
}
void SealMaid::reminiscenceSet()
{
    int point = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStructX->gameCharacter[i]->characterPic->isClicked)
        {
            point = i;
            break;
        }
    }
    for(int i = 0;i < paintStructX->gameCharacter[point]->statusNum;i++)
    {
        if(cardList->getType(paintStructX->gameCharacter[point]->status[i]) == magic)
        {
            switch(cardList->getName(paintStructX->gameCharacter[point]->status[i]))
            {
                case poison:sealBreak->skillGroup[0]->canBeClicked = true;break;
                case weak:sealBreak->skillGroup[1]->canBeClicked = true;break;
                case shield:sealBreak->skillGroup[2]->canBeClicked = true;break;
            }
        }
        else
        {
            if(cardList->getSkillOne(paintStructX->gameCharacter[point]->status[i])/10 == 4)
            {
                sealBreak->skillGroup[cardList->getSkillOne(card[i]) % 10 + 2]->canBeClicked = true;
            }
            else
            {
                sealBreak->skillGroup[cardList->getSkillOne(card[i]) % 10 + 7]->canBeClicked = true;
            }
        }
    }
}
void Angel::selfReset()
{

}
