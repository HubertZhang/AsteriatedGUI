#include "priestmaid.h"

PriestMaid::PriestMaid(PaintStruct* paintStruct,QWidget *parent,Window* sacredX) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    magicCount = 0;
    sacredZoneCount = 0;
    cureCount = 0;
    sacredContractPaint = false;
    dialog = new NewDialog(windowX);
    dialog->init(15);//神圣启示
    int info[3] = {2,0,0};
    sacredContract = new NumberDialog(paintStruct,parent);
    for(int i = 0;i < 5;i++)
    {
        sacredContract->number[i]->setChecked(false);
        sacredContract->number[i]->setCheckable(false);
    }
    sacredContract->ensure->setChecked(false);
    sacredContract->ensure->setCheckable(false);
    sacredContract->cancel->setChecked(false);
    sacredContract->cancel->setCheckable(false);
    for(int i = 0;i < 5;i++)
    {
        connect(sacredContract->number[i],SIGNAL(changeClicked()),this,SLOT(contractSet()));
        connect(sacredContract->number[i],SIGNAL(notClicked()),this,SLOT(contractReset()));
        disconnect(sacredContract->number[i],SIGNAL(changeClicked()),sacredContract->ensure,SLOT(recoverClick()));
    }
    magicGroup[0] = new PicButton(108,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(109,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(111,568,559,100,42,false,this);
    magicGroup[3] = new PicButton(112,671,559,100,42,false,this);
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
void PriestMaid::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(5);
    magicGroup[0]->setChecked(true);
}
void PriestMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[1]->setChecked(true);
}
void PriestMaid::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(8);
    magicGroup[2]->setChecked(true);
}
void PriestMaid::magicSetThree()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(9);
    magicGroup[3]->setChecked(true);
}
void PriestMaid::changeSelfMode(int mode)
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
        case 4://神圣启示响应阶段
        {
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            emit resetSignal();
            break;
        }
        case 5://神圣祈福响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < cardNum;j++)
                {
                    if(i != j)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
                    }
                }
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(magicPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicMinus()));
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            break;
        }
        case 6://水之神力响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == water)
                {
                    cardButton[i]->setCheckable(true);
                }
                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(waterPhase()));
            break;
        }
        case 7://神圣契约响应阶段
        {
            informationKind = 300;
            for(int i = 0;i < 4;i++)
            {
                magicGroup[i]->setCheckable(false);
            }
            for(int i = 0;i < paintStruct->gameCharacter[5]->cure && i < 5;i++)
            {
                sacredContract->number[i]->setCheckable(true);
            }
            sacredContractPaint = true;
            break;
        }
        case 8://神圣领域(1)响应阶段
        {
            cancel->setCheckable(false);
            if(cardNum == 0)
            {
                for(int i = 0;i < 6;i++)
                {
                    paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                }
            }
            else if(cardNum == 1)
            {
                cardButton[0]->setCheckable(true);
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
                    connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(zonePlus()));
                    connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(zoneMinus()));
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
        case 9://神圣领域2响应阶段
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
                    connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(curePlus()));
                    connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(cureMinus()));
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
        case 10://水之神力响应第二阶段
        {
            cancel->setCheckable(false);
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            for(int i = 0;i < cardNum;i++)
            {
                cardButton[i]->setCheckable(true);
            }
            for(int i = 0;i < 4;i++)
            {
                magicGroup[i]->setCheckable(false);
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
    }
}
//void PriestMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//    }
//    if(sacredContractPaint)
//    {
//        sacredContract->paint(event,painter);
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
void PriestMaid::setFrame()
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
void PriestMaid::skillset()
{
    int magicNum = 0;
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getNature(card[i]) == water)
        {
            magicGroup[1]->setCheckable(true);
        }
        if(cardList->getType(card[i]) == magic)
        {
            magicNum ++;
        }
    }
    if(magicNum > 1)
    {
        magicGroup[0]->setCheckable(true);
    }
    if(paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal != 0)
    {
        if(paintStruct->gameCharacter[5]->cure != 0)
        {
            magicGroup[2]->setCheckable(true);
        }
        magicGroup[3]->setCheckable(true);
    }
}
void PriestMaid::skillCancel()
{
    ask = false;
    dialog->label->hide();
    sacredContract->labelOne->hide();
    sacredContract->labelTwo->hide();
    sacredContractPaint = false;
    sacredZoneCount = 0;
    cureCount = 0;
    magicCount = 0;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
    for(int i = 0;i < 5;i++)
    {
        sacredContract->number[i]->setChecked(false);
        sacredContract->number[i]->setCheckable(false);
    }
    sacredContract->ensure->setChecked(false);
    sacredContract->ensure->setCheckable(false);
    sacredContract->cancel->setChecked(false);
    sacredContract->cancel->setCheckable(false);
    disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(waterPhase()));
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(curePlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(cureMinus()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(zonePlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(zoneMinus()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(magicPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicMinus()));
    }
    for(int i = 0;i < 4;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
}
void PriestMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void PriestMaid::magicPlus()
{
    if(magicCount == 0)
    {
        magicCount ++;
        return;
    }
    if(magicCount == 1)
    {
        magicCount ++;
        ensure->setCheckable(true);
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isChecked())
            {
                cardButton[i]->setCheckable(false);
            }
        }
        return;
    }
}
void PriestMaid::magicMinus()
{
    if(magicCount == 2)
    {
        ensure->setCheckable(false);
        magicCount --;
        for(int i = 0;i < cardNum;i++)
        {
            if(cardList->getType(card[i]) == magic)
            {
                cardButton[i]->setCheckable(true);
            }
        }
        return;
    }
    if(magicCount == 1)
    {
        magicSetZero();
        return;
    }
}
void PriestMaid::waterPhase()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(10);
    magicGroup[1]->setChecked(true);
}
void PriestMaid::zonePlus()
{
    if(sacredZoneCount == 0)
    {
        sacredZoneCount ++;
        return;
    }
    if(sacredZoneCount == 1)
    {
        sacredZoneCount ++;
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isChecked())
            {
                cardButton[i]->setCheckable(false);
            }
        }
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        }
        return;
    }
}
void PriestMaid::zoneMinus()
{
    if(sacredZoneCount == 2)
    {
        sacredZoneCount --;
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
    if(sacredZoneCount == 1)
    {
        magicSetTwo();
    }
}
void PriestMaid::curePlus()
{
    if(cureCount == 0)
    {
        cureCount ++;
        return;
    }
    if(cureCount == 1)
    {
        cureCount ++;
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
void PriestMaid::cureMinus()
{
    if(cureCount == 2)
    {
        cureCount --;
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
    if(cureCount == 1)
    {
        magicSetThree();
    }
}

void PriestMaid::selfReset()
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
void PriestMaid::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void PriestMaid::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void PriestMaid::contractSet()
{
    for(int i = 0;i < 5;i++)
    {
        if(paintStruct->gameCharacter[i]->color == paintStruct->gameCharacter[5]->color)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        }
    }
}
void PriestMaid::contractReset()
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
void PriestMaid::priestAct()
{
    linkReset();
    skillset();
    changeSelfMode(7);
}
void PriestMaid::sendMessageSelf()
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
        case 100://神圣启示响应阶段
        {
            tempMes.push_back(1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://神圣祈福响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://水之神力响应阶段
        {
            tempMes.push_back(1);
            if(magicGroup[1]->isCheckable())//一阶段
            {
                tempMes.push_back(3);
            }
            else//二阶段
            {
                tempMes.push_back(4);
                putCharacter(tempMes);
            }
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 202://神圣领域（1）响应阶段
        case 203://神圣领域（2）响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(informationKind - 197);
            putCharacter(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 300://神圣契约响应阶段
        {
            putCharacter(tempMes);
            for(int i = 0;i < 5;i++)
            {
                if(sacredContract->number[i]->isChecked())
                {
                    tempMes.push_back(i + 1);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
        }
        default:
        {
            sendMessageIn();
        }
    }
}
