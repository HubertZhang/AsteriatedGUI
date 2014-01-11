#include "swordking.h"

SwordKing::SwordKing(PaintStruct* paintStruct,QWidget *parent,Window* swordX) :
    CardAndSkill(paintStruct,parent)
{
    lastAttack = 0;
    ask = false;
    swordAsk = false;
    dialog = new NewDialog(windowX);
    dialog->init(19);//剑魂守护,剑气斩,天使之魂,恶魔之魂,不屈意志
    int info[3] = {2,0,0};
    swordCut = new NumberDialog(paintStruct,parent);
    swordCut->ensure->setCheckable(false);
    swordCut->cancel->setCheckable(false);
    swordCut->ensure->setChecked(false);
    swordCut->cancel->setChecked(false);
    for(int i = 0;i < 5;i++)
    {
        connect(swordCut->number[i],SIGNAL(beChecked()),this,SLOT(attackSet()));
        connect(swordCut->number[i],SIGNAL(unChecked()),this,SLOT(attackReset()));
        swordCut->number[i]->setChecked(false);
        swordCut->number[i]->setCheckable(false);
        disconnect(swordCut->number[i],SIGNAL(beChecked()),swordCut->ensure,SLOT(setCheckableTrue()));
    }
    disconnect(swordCut->ensure,SIGNAL(beChecked()),swordCut,SLOT(destroyLabel()));
    disconnect(swordCut->cancel,SIGNAL(beChecked()),swordCut,SLOT(destroyLabel()));
    connect(swordCut->ensure,SIGNAL(beChecked()),this,SLOT(reset()));
    connect(swordCut->cancel,SIGNAL(beChecked()),this,SLOT(reset()));
    for(int i = 0;i < dialog->skillCount;i++)
    {
        for(int j = 0;j < dialog->skillCount;j++)
        {
            if(i != j)
            {
                connect(dialog->skillGroup[i],SIGNAL(beChecked()),dialog->skillGroup[j],SLOT(setCheckedFalse()));
            }
        }
        connect(dialog->skillGroup[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(dialog->skillGroup[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
}
void SwordKing::changeSelfMode(int mode)
{
    cancel->setCheckable(true);
    disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
    switch(mode)
    {
        case 4://剑魂守护响应阶段
        case 6://天使之魂响应阶段
        case 7://恶魔之魂响应阶段
        case 8://不屈意志响应阶段
        {
            emit resetSignal();
            break;
        }
        case 5://剑气斩响应阶段
        {
            swordAsk = true;
            swordCut->ensure->setCheckable(false);
            int yellowUse = paintStruct->gameCharacter[5]->yellow;
            if(yellowUse > 3)
            {
                yellowUse = 3;
            }
            for(int i = 0;i < 5;i++)
            {
                if(i < yellowUse)
                {
                    swordCut->number[i]->setCheckable(true);
                }
                else
                {
                    swordCut->number[i]->setCheckable(false);
                }
            }
            break;
        }
    }
}
//void SwordKing::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//    }
//    if(swordAsk)
//    {
//        swordCut->paint(event,painter);
//        swordCut->labelOne->setText("剑气");
//        swordCut->labelTwo->setText("");
//        swordCut->labelOne->show();
//        swordCut->labelTwo->show();
//    }
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    for(int i = 0;i < cardNum;i++)
//    {
//        cardButton[i]->paint(event,painter);
//    }
//}
void SwordKing::setFrame()
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
void SwordKing::skillCancel()
{
    ask = false;
    swordAsk = false;
    swordCut->labelOne->hide();
    swordCut->labelTwo->hide();
    swordCut->ensure->setCheckable(false);
    swordCut->cancel->setCheckable(false);
    swordCut->ensure->setChecked(false);
    swordCut->cancel->setChecked(false);
    dialog->label->hide();
    for(int i = 0;i < 5;i++)
    {
        swordCut->number[i]->setChecked(false);
        swordCut->number[i]->setCheckable(false);
    }
}
void SwordKing::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            changeSelfMode(4 + i);
        }
    }
    dialogReset();
}
void SwordKing::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void SwordKing::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void SwordKing::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            informationKind = 100 + i;
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
        case 100://剑魂守护响应阶段
        case 102://天使之魂响应阶段
        case 103://恶魔之魂响应阶段
        case 104://不屈意志响应阶段
        {
            tempMes.push_back(informationKind - 99);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 101://剑气斩
        {
            for(int i = 0;i < 3;i++)
            {
                if(swordCut->number[i]->isChecked())
                {
                    putCharacter(tempMes);
                    tempMes.push_back(i + 1);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(2);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
void SwordKing::attackSet()
{
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
        if(i != lastAttack)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
            connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        }
    }
    ensure->setChecked(false);
}
void SwordKing::attackReset()
{
    for(int i = 0;i < 6;i++)
    {
        paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
        paintStruct->gameCharacter[i]->characterPic->setChecked(false);
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
}
void SwordKing::lastAttackSet(int m)
{
    lastAttack = m;
}
