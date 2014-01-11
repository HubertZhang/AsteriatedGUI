#include "praymaid.h"

PrayMaid::PrayMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    lightCount = 0;
    dialog = new NewDialog(windowX);
    dialog->init(16);//法力潮汐
    magicGroup[0] = new PicButton(113,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(114,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(115,568,559,100,42,false,this);
    magicGroup[3] = new PicButton(116,671,559,100,42,false,this);
    for(int i = 0;i < dialog->skillCount;i++)
    {
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    for(int i = 0;i < 4;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),magicGroup[i],SLOT(isThisClicked(int,int)));
    }
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
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
    connect(magicGroup[3],SIGNAL(changeClicked()),this,SLOT(magicSetThree()));
    for(int i = 0;i < 4;i++)
    {
        connect(magicGroup[i],SIGNAL(notClicked()),this,SLOT(skillClear()));
    }
}
void PrayMaid::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->setChecked(true);
}
void PrayMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->setChecked(true);
}
void PrayMaid::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[2]->setChecked(true);
}
void PrayMaid::magicSetThree()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(7);
    magicGroup[3]->setChecked(true);
}
void PrayMaid::changeSelfMode(int mode)
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
        case 4://光辉信仰响应阶段
        {
            cancel->setCheckable(false);
            if(cardNum == 0)
            {
                for(int i = 0;i < 5;i++)
                {
                    if(paintStruct->gameCharacter[i]->color == paintStruct->gameCharacter[5]->color)
                    {
                        paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                    }
                }
            }
            else if(cardNum == 1)
            {
                cardButton[0]->setCheckable(true);
                for(int j = 0;j < 5;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[0],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[0],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    else
                    {
                        connect(cardButton[0],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        connect(cardButton[0],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    cardButton[i]->setCheckable(true);
                    for(int j = 0;j < cardNum;j++)
                    {
                        if(i != j)
                        {
                            disconnect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
                        }
                    }
                    connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(lightPlus()));
                    connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(lightMinus()));
                    for(int j = 0;j < 6;j++)
                    {
                        if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                        {
                            disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                            disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                        }
                    }
                }
            }
            break;
        }
        case 5://漆黑信仰响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            }
            break;
        }
        case 6://威力赐福响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i]) == 161)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 5;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    else
                    {
                        connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            break;
        }
        case 7://迅捷赐福响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i]) == 162)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 5;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    else
                    {
                        connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            break;
        }
        case 8://法力潮汐响应阶段
        {
            cancel->setCheckable(true);
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            emit resetSignal();
            break;
        }
    }
}
//void PrayMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//    }
//    for(int i = 0;i < 4;i++)
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
void PrayMaid::setFrame()
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
void PrayMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillOne(card[i]) == 161)
        {
            magicGroup[2]->setCheckable(true);
        }
        if(cardList->getSkillOne(card[i]) == 162)
        {
            magicGroup[3]->setCheckable(true);
        }
    }
    if(paintStruct->gameCharacter[5]->activated && paintStruct->gameCharacter[5]->yellow)
    {
        magicGroup[0]->setCheckable(true);
        magicGroup[1]->setCheckable(true);
    }
}
void PrayMaid::skillCancel()
{
    ask = false;
    dialog->label->hide();
    lightCount = 0;
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(lightPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(lightMinus()));
    }
    for(int i = 0;i < 4;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
}
void PrayMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void PrayMaid::lightPlus()
{
    if(lightCount == 0)
    {
        lightCount ++;
        return;
    }
    if(lightCount == 1)
    {
        lightCount ++;
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isChecked())
            {
                cardButton[i]->setCheckable(false);
            }
        }
        for(int i = 0;i < 5;i++)
        {
            if(paintStruct->gameCharacter[i]->color == paintStruct->gameCharacter[5]->color)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            }
        }
        return;
    }
}
void PrayMaid::lightMinus()
{
    if(lightCount == 2)
    {
        lightCount --;
        ensure->setCheckable(false);
        for(int i = 0;i < cardNum;i++)
        {
            cardButton[i]->setCheckable(true);
        }
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
        }
        return;
    }
    if(lightCount == 1)
    {
        magicSetZero();
    }
}

void PrayMaid::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            changeSelfMode(8);
        }
    }
    dialogReset();
}
void PrayMaid::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void PrayMaid::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void PrayMaid::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            informationKind = 100 + i;
        }
    }
    for(int i = 0;i < 4;i++)
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
        case 100://法力潮汐响应阶段
        {
            tempMes.push_back(5);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://光辉响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            putCharacter(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://漆黑信仰响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            putCharacter(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;

        }
        case 202://威力赐福响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(3);
            putCharacter(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 203://迅捷赐福响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
            putCharacter(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
