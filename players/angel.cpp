#include "angel.h"
#include <QString>
#include <iostream>
using namespace std;
Angel::Angel(PaintStruct* paintStruct,QWidget *parent,Window* windowAngel) :
    CardAndSkill(paintStruct,parent)
{
    reminiscence = false;
    ask = false;
    proAsk = false;
    blessCount = 0;
    dialog = new NewDialog(windowX);
    windClear = new NewDialog(windowX);
    int info[3] = {2,0,0};
    kamiPro = new NumberDialog(paintStruct,parent);
    dialog->init(7);//天使之歌,神之庇护
    windClear->init(101);
    connect(kamiPro->ensure,SIGNAL(beChecked()),this,SLOT(reset()));
    connect(kamiPro->cancel,SIGNAL(beChecked()),this,SLOT(reset()));
    disconnect(kamiPro->ensure,SIGNAL(beChecked()),kamiPro,SLOT(destroyLabel()));
    disconnect(kamiPro->cancel,SIGNAL(beChecked()),kamiPro,SLOT(destroyLabel()));
    magicGroup[0] = new PicButton(75,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(76,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(77,568,559,100,42,false,this);
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 2;j++)
        {
            if(i != j)
            {
                connect(dialog->skillGroup[i],SIGNAL(beChecked()),dialog->skillGroup[j],SLOT(setCheckedFalse()));
            }
        }
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
        connect(dialog->skillGroup[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(dialog->skillGroup[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            if(i != j)
            {
                connect(magicGroup[i],SIGNAL(beChecked()),magicGroup[j],SLOT(setCheckedFalse()));
            }
        }
    }
    for(int i = 0;i < 10;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),windClear->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    connect(magicGroup[0],SIGNAL(beChecked()),this,SLOT(magicSetZero()));
    connect(magicGroup[1],SIGNAL(beChecked()),this,SLOT(magicSetOne()));
    connect(magicGroup[2],SIGNAL(beChecked()),this,SLOT(magicSetTwo()));
    for(int i = 0;i < 3;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),magicGroup[i],SLOT(isThisClicked(int,int)));
        connect(magicGroup[i],SIGNAL(unChecked()),this,SLOT(skillClear()));
    }
    for(int i = 0;i < 10;i++)
    {
        connect(windClear->skillGroup[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(windClear->skillGroup[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        for(int j = 0;j < 10;j++)
        {
            if(i != j)
            {
                connect(windClear->skillGroup[i],SIGNAL(beChecked()),windClear->skillGroup[j],SLOT(setCheckedFalse()));
            }
        }
    }
}
void Angel::magicSetZero()
{
    linkReset();
    skillset();
    for(int i = 0;i < 10;i++)
    {
        windClear->skillGroup[i]->setChecked(false);
    }
    changeSelfMode(4);
    magicGroup[0]->setChecked(true);
}
void Angel::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->setChecked(true);
}
void Angel::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->setChecked(true);
}
void Angel::changeSelfMode(int mode)
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
        for(int j = 0;j < 6;j++)
        {
            if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
    }
    cancel->setCheckable(true);
    switch(mode)
    {
        case 4://风之洁净响应阶段
        {
            cancel->setCheckable(false);
            reminiscence = true;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == wind)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                }
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(reminiscenceSet()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(reminiscenceReset()));
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
            }
            break;
        }
        case 5://天使祝福响应阶段
        {
            cancel->setCheckable(false);
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == water)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(countPlus()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(countMinus()));
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
               }
            }
            for(int i = 0;i < 6;i++)
            {
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                for(int j = 0;j < 6;j ++)
                {
                    if(i != j)
                    {
                        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
                    }
                }
            }
            //disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
        case 6://天使之墙响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillTwo(card[i]) == 71)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                    bool shieldExist = false;
                    for(int k = 0;k < paintStruct->gameCharacter[j]->statusNum;k++)
                    {
                        if(cardList->getName(paintStruct->gameCharacter[j]->status[k]) == shield || cardList->getSkillTwo(paintStruct->gameCharacter[j]->status[k]) == 71)
                        {
                            //system("pause");
                            shieldExist = true;
                            break;
                        }
                    }
                    if(!shieldExist)
                    {
                        connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                }
            }
            break;
        }
        case 7://天使之歌响应阶段
        {
        //  cancel->setCheckable(false);
            reminiscence = true;
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    paintStruct->gameCharacter[j]->characterPic->setCheckable(true);
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                }
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(reminiscenceSet()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(reminiscenceReset()));
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
            }
            disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
        case 8://神之庇护
        {
            proAsk = true;
            int protect = morale;
            if(paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal < morale)
            {
                protect = paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal;
            }            
            for(int i = 0;i < 5;i++)
            {
                if(i < protect)
                {
                    kamiPro->number[i]->setCheckable(true);
                }
                else
                {
                    kamiPro->number[i]->setCheckable(false);
                }
            }
            disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
    }
}
//void Angel::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(reminiscence)
//    {
//        windClear->paint(event,painter);
//    }
//    if(proAsk)
//    {
//        kamiPro->paint(event,painter);
//    }
//    if(ask)
//    {
//        dialog->paint(event,painter);
//        cancel->setCheckable(true);
//    }
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
void Angel::setFrame()
{
    ask = true;
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setChecked(false);
    }
}*/
void Angel::skillset()
{
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getNature(card[i]) == wind)
        {
            magicGroup[0]->setCheckable(true);
        }
        if(cardList->getNature(card[i]) == water)
        {
            magicGroup[1]->setCheckable(true);
        }
        if(cardList->getSkillTwo(card[i]) == 71)
        {
            magicGroup[2]->setCheckable(true);
        }
    }
}
void Angel::skillCancel()
{
    blessCount = 0;
    ask = false;
    proAsk = false;
    reminiscence = false;
    windClear->label->hide();
    kamiPro->labelOne->hide();
    kamiPro->labelTwo->hide();
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(reminiscenceSet()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(reminiscenceReset()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(countPlus()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(countMinus()));
    }
    //pureCureFrame->reset();

}
void Angel::skillClear()
{
    int info[3] = {0,0,0};
    windClear->label->hide();
    kamiPro->labelOne->hide();
    kamiPro->labelTwo->hide();
    reminiscence = false;
    proAsk = false;
    for(int i = 0;i < 5;i++)
    {
        kamiPro->number[i]->setChecked(false);
    }
    kamiPro->ensure->setChecked(false);
    kamiPro->cancel->setChecked(false);
    linkReset();
    changePaintMode(2,info);
}
void Angel::countPlus()
{
    ensure->setCheckable(true);
    if(blessCount < 2)
    {
        blessCount ++;
    }
    else
    {
        for(int i = 0;i < 6;i++)
        {
            if(paintStruct->gameCharacter[i]->characterPic->isChecked())
            {
                paintStruct->gameCharacter[i]->characterPic->setChecked(false);
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
        ensure->setCheckable(false);
    }
}
void Angel::reminiscenceReset()
{
    for(int i = 0;i < 10;i++)
    {
        windClear->skillGroup[i]->setCheckable(false);
    }
    ensure->setCheckable(false);
}
void Angel::reminiscenceSet()
{
    reminiscenceReset();
    int point = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            point = i;
            break;
        }
    }
    for(int i = 0;i < paintStruct->gameCharacter[point]->statusNum;i++)
    {
        if(cardList->getType(paintStruct->gameCharacter[point]->status[i]) == magic)
        {
            switch(cardList->getName(paintStruct->gameCharacter[point]->status[i]))
            {
                case poison:windClear->skillGroup[0]->setCheckable(true);break;
                case weak:windClear->skillGroup[1]->setCheckable(true);break;
                case shield:windClear->skillGroup[2]->setCheckable(true);break;
            }
        }
        else
        {
            if(cardList->getSkillOne(paintStruct->gameCharacter[point]->status[i])/10 == 4)
            {
                windClear->skillGroup[cardList->getSkillOne(card[i]) % 10 + 2]->setCheckable(true);
            }
            else
            {
                windClear->skillGroup[cardList->getSkillOne(card[i]) % 10 + 7]->setCheckable(true);
            }
        }
    }
}
void Angel::selfReset()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            changeSelfMode(7 + i);
        }
    }
    dialogReset();
}
void Angel::setResPara(int para)
{
    morale = para;
}
void Angel::dialogReset()
{
    //system("pause");
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void Angel::dialogSet(bool canX[])
{
    dialog->set(canX);
}
