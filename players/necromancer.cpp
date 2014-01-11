#include "necromancer.h"

Necromancer::Necromancer(PaintStruct* paintStruct,QWidget *parent,Window* deathX) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    deathPaint = false;
    deathCount = 0;
    dialog = new NewDialog(windowX);
    dialog->init(13);//不朽
    int info[3] = {2,0,0};
    deathTouch = new NumberDialog(paintStruct,parent);
    deathTouch->cancel->setCheckable(false);
    for(int i = 0;i < 5;i++)
    {
        connect(deathTouch->number[i],SIGNAL(beChecked()),this,SLOT(deathSet()));
        connect(deathTouch->number[i],SIGNAL(unChecked()),this,SLOT(deathReset()));
        disconnect(deathTouch->number[i],SIGNAL(beChecked()),deathTouch->ensure,SLOT(setCheckableTrue()));
    }
    magicGroup[0] = new PicButton(98,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(99,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(100,568,559,100,42,false,this);
    for(int i = 0;i < dialog->skillCount;i++)
    {
        connect(dialog->skillGroup[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(dialog->skillGroup[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
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
                connect(magicGroup[i],SIGNAL(beChecked()),magicGroup[j],SLOT(setCheckedFalse()));
            }
        }
    }
    //system("pause");
    connect(magicGroup[0],SIGNAL(beChecked()),this,SLOT(magicSetZero()));
    connect(magicGroup[1],SIGNAL(beChecked()),this,SLOT(magicSetOne()));
    connect(magicGroup[2],SIGNAL(beChecked()),this,SLOT(magicSetTwo()));
    for(int i = 0;i < 3;i++)
    {
        connect(magicGroup[i],SIGNAL(unChecked()),this,SLOT(skillClear()));
    }
}
void Necromancer::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(5);
    magicGroup[0]->setChecked(true);
}
void Necromancer::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[1]->setChecked(true);
}
void Necromancer::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(7);
    magicGroup[2]->setChecked(true);
}
void Necromancer::changeSelfMode(int mode)
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
        case 4://不朽响应阶段
        {
            disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            emit resetSignal();
            break;
        }
        case 5://瘟疫响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == ground)
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
                    }
                }
                connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
            }
            disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
        case 6://死亡之触响应阶段
        {
            cancel->setCheckable(false);
            deathPaint = true;
            for(int i = 0;i < 6;i++)
            {
                cardButton[i]->setCheckable(true);
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
                    }
                }
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                }
                connect(cardButton[i],SIGNAL(beChecked()),this,SLOT(countPlus()));
                connect(cardButton[i],SIGNAL(unChecked()),this,SLOT(countMinus()));
            }
            break;
        }
        case 7://墓碑陨落响应阶段
        {
            cancel->setCheckable(false);
            ensure->setCheckable(true);
            break;
        }
    }
}
//void Necromancer::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//    }
//    if(deathPaint)
//    {
//        deathTouch->paint(event,painter);
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
void Necromancer::setFrame()
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
void Necromancer::skillset()
{
    int detect[7];
    for(int i = 0;i < 7;i++)
    {
        detect[i] = 0;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getNature(card[i]) == ground)
        {
            magicGroup[0]->setCheckable(true);
        }
        detect[cardList->getNature(card[i])] ++;
    }
    bool tem = false;
    for(int i = 0;i < 7;i++)
    {
        if(detect[i] > 1)
        {
            tem = true;
            break;
        }
    }
    if(paintStruct->gameCharacter[5]->cure < 2)
    {
        tem = false;
    }
    magicGroup[1]->setCheckable(tem);
    if(paintStruct->gameCharacter[5]->gem!= 0)
    {
        magicGroup[2]->setCheckable(true);
    }
}
void Necromancer::skillCancel()
{
    ask = false;
    dialog->label->hide();
    deathPaint = false;
    deathCount = 0;
    for(int i = 0;i < 5;i++)
    {
        deathTouch->number[i]->setChecked(false);
        deathTouch->number[i]->setCheckable(false);
    }
    deathTouch->ensure->setChecked(false);
    deathTouch->cancel->setChecked(false);
    deathTouch->labelOne->hide();
    deathTouch->labelTwo->hide();
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(beChecked()),this,SLOT(countPlus()));
        disconnect(cardButton[i],SIGNAL(unChecked()),this,SLOT(countMinus()));
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
}
void Necromancer::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void Necromancer::countPlus()
{
    if(deathCount == 0)
    {
        deathCount ++;
        int attribute;
        for(int i = 0;i < cardNum;i++)
        {
            if(cardButton[i]->isChecked())
            {
                attribute = cardList->getNature(card[i]);
                break;
            }
        }
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getNature(card[i]) != attribute)
            {
                cardButton[i]->setCheckable(false);
            }
        }
        return;
    }
    if(deathCount == 1)
    {
        deathCount ++;
        for(int i = 0;i < paintStruct->gameCharacter[5]->cure;i++)
        {
            deathTouch->number[i]->setCheckable(true);
        }
        return;
    }
}
void Necromancer::countMinus()
{
    if(deathCount == 2)
    {
        deathCount --;
        for(int i = 0;i < 5;i++)
        {
            deathTouch->number[i]->setCheckable(false);
        }
        return;
    }
    if(deathCount == 1)
    {
        magicSetOne();
    }
}
void Necromancer::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            changeSelfMode(4);
        }
    }
    dialogReset();
}
void Necromancer::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void Necromancer::dialogSet(bool canX[])
{
    dialog->set(canX);
}

void Necromancer::deathSet()
{
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->color != paintStruct->gameCharacter[5]->color)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        }
    }
}
void Necromancer::deathReset()
{
    ensure->setCheckable(false);
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->color != paintStruct->gameCharacter[5]->color)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
        }
    }
}
void Necromancer::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            informationKind = 100 + i;
        }
    }
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
        case 100://不朽响应阶段
        {
            tempMes.push_back(1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://瘟疫响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://死亡之触响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(3);
            putCharacter(tempMes);
            for(int i = 0;i < 5;i++)
            {
                if(deathTouch->number[i]->isChecked())
                {
                    tempMes.push_back(i + 1);
                }
            }
            putCardCount(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;

        }
        case 202://墓碑陨落响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
