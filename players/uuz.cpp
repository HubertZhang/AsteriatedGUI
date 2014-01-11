#include "uuz.h"

UUZ::UUZ(PaintStruct* paintStruct,QWidget *parent,Window* soulX):
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    soulAsk = false;
    linkDamage = 0;
    dialog = new NewDialog(windowX);
    dialog->init(22);//灵魂转换（黄）,灵魂转换（蓝）,灵魂链接
    int info[3] = {2,0,0};
    soulCount = 0;
    mirrorCount = 0;
    mirrorLine = 0;
    soulLink = new NumberDialog(paintStruct,parent);
    soulLink->ensure->setCheckable(false);
    soulLink->cancel->setCheckable(false);
    soulLink->ensure->setChecked(false);
    soulLink->cancel->setChecked(false);
    for(int i = 0;i < 5;i++)
    {
        soulLink->number[i]->setChecked(false);
        soulLink->number[i]->setCheckable(false);
    }
    connect(soulLink->ensure,SIGNAL(changeClicked()),this,SLOT(sendMessageCardAndSkill()));
    connect(soulLink->cancel,SIGNAL(changeClicked()),this,SLOT(sendMessageCardAndSkill()));
    disconnect(soulLink->ensure,SIGNAL(changeClicked()),soulLink,SLOT(destroyLabel()));
    disconnect(soulLink->cancel,SIGNAL(changeClicked()),soulLink,SLOT(destroyLabel()));
    connect(soulLink->ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
    connect(soulLink->cancel,SIGNAL(changeClicked()),this,SLOT(reset()));
    magicGroup[0] = new PicButton(143,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(146,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(147,568,559,100,42,false,this);
    magicGroup[3] = new PicButton(148,671,559,100,42,false,this);
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
void UUZ::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->setChecked(true);
}
void UUZ::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(7);
    magicGroup[1]->setChecked(true);
}
void UUZ::magicSetTwo()
{
    linkReset();
    skillset();
    changeSelfMode(8);
    magicGroup[2]->setChecked(true);
}
void UUZ::magicSetThree()
{
    linkReset();
    skillset();
    changeSelfMode(9);
    magicGroup[3]->setChecked(true);
}
void UUZ::changeSelfMode(int mode)
{
    switch(mode)
    {
        case 4://灵魂召还响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->setCheckable(true);
                }
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(soulPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(soulMinus()));
            }
            break;
        }
        case 5://灵魂Y to B响应阶段
        case 6://灵魂B to Y响应阶段
        {
            emit resetSignal();
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 7://灵魂镜像响应阶段
        {
            cardSetOne();
            if(cardNum > 2)
            {
                mirrorLine = 3;
            }
            else
            {
                mirrorLine = cardNum;
                if(!cardNum)
                {
                    clickAllSet();
                    singleToEnsure();
                    return;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(mirrorPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(mirrorMinus()));
            }
            break;
        }
        case 8://灵魂震爆响应阶段
        case 9://灵魂赐予响应阶段
        {
            cardSingleSet(213 + mode);
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(clickAllSet()));
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(singleToEnsure()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(allReset()));
            }
            break;
        }
        case 10://灵魂链接响应阶段
        {
            soulAsk = true;
            soulLink->ensure->setCheckable(false);
            for(int i = 0;i < 5;i++)
            {
                if(i < linkDamage && i < paintStruct->gameCharacter[5]->blue)
                {
                    soulLink->number[i]->setCheckable(true);
                }
                else
                {
                    soulLink->number[i]->setCheckable(false);
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
    }
}
//void UUZ::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//    }
//    if(soulAsk)
//    {
//        soulLink->paint(event,painter);
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
void UUZ::setFrame()
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
void UUZ::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getType(card[i]) == magic)
        {
            magicGroup[0]->setCheckable(true);
        }
        if(cardList->getSkillTwo(card[i]) == 221 && paintStruct->gameCharacter[5]->yellow > 2)
        {
            magicGroup[2]->setCheckable(true);
        }
        if(cardList->getSkillTwo(card[i]) == 222 && paintStruct->gameCharacter[5]->blue > 2)
        {
            magicGroup[3]->setCheckable(true);
        }
    }
    if(paintStruct->gameCharacter[5]->yellow > 1)
    {
        magicGroup[1]->setCheckable(true);
    }
}
void UUZ::skillCancel()
{
    ask = false;
    soulAsk = false;
    mirrorCount = 0;
    soulCount = 0;
    soulLink->labelOne->hide();
    soulLink->labelTwo->hide();
    for(int i = 0;i < 4;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
    soulLink->ensure->setCheckable(false);
    soulLink->cancel->setCheckable(false);
    soulLink->ensure->setChecked(false);
    soulLink->cancel->setChecked(false);
    for(int i = 0;i < 5;i++)
    {
        soulLink->number[i]->setChecked(false);
        soulLink->number[i]->setCheckable(false);
    }
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(clickAllSet()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(singleToEnsure()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(allReset()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(mirrorPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(mirrorMinus()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(soulPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(soulMinus()));
    }
}
void UUZ::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void UUZ::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            if(i > 1)
            {
                changeSelfMode(10);
            }
            else
            {
                changeSelfMode(5 + i);
            }
        }
    }
    dialogReset();
}
void UUZ::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void UUZ::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void UUZ::sendMessageSelf()
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
        case 6://灵魂链接
        {
            putCharacter(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 100://灵魂转换Y to B
        case 101://灵魂转换B to Y
        {
            tempMes.push_back(informationKind - 98);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 102://灵魂链接响应阶段
        {
        //system("pause");
            if(soulLink->cancel->isChecked())
            {
                tempMes.push_back(-1);
                emit sendMessageSelfSig(tempMes);
                return;
            }
            for(int i = 0;i < 5;i++)
            {
                if(soulLink->number[i]->isChecked())
                {
                    tempMes.push_back(i + 1);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(7);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://灵魂召还响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            putCardCount(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://灵魂镜像响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
            putCharacter(tempMes);
            putCardCount(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 202://灵魂震爆响应阶段
        case 203://灵魂赐予响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(informationKind - 197);
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
void UUZ::damageSet(int x)
{
    linkDamage = x;
}
void UUZ::soulPlus()
{
    soulCount ++;
    ensure->setCheckable(true);
}
void UUZ::soulMinus()
{
    soulCount --;
    if(!soulCount)
    {
        ensure->setCheckable(false);
    }
}
void UUZ::mirrorPlus()
{
    mirrorCount ++;
    if(mirrorCount == mirrorLine)
    {
        clickAllSet();
        singleToEnsure();
        cardResetOne();
    }
}
void UUZ::mirrorMinus()
{
    mirrorCount --;
    cardSetOne();
    allReset();
    ensure->setCheckable(false);
}
