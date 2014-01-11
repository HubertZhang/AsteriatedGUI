#include "hakureireimu.h"

HakureiReimu::HakureiReimu(PaintStruct* paintStruct,QWidget *parent,Window* showX) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    cardRecord = 0;
    showRecord = false;
    dialog = new NewDialog(windowX);
    elementCount = 0;
    dialog->init(18);//念咒,百鬼夜行,灵力崩解
    magicGroup[0] = new PicButton(122,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(123,465,559,100,42,false,this);
    int info[3] = {0,0,0};
    showFirePaint = false;
    showFire = new SpecialDialog(paintStruct,parent);
    showFire->labelOne->hide();
    showFire->labelOne->setText("展示火系");
    showFire->labelTwo->setText("");
    showFire->ensure->setCheckable(false);
    showFire->cancel->setCheckable(false);
    connect(showFire->ensure,SIGNAL(changeClicked()),this,SLOT(fireChoose()));
    connect(showFire->cancel,SIGNAL(changeClicked()),this,SLOT(fireNotChoose()));
    disconnect(showFire->ensure,SIGNAL(changeClicked()),showFire,SLOT(destroyLabel()));
    disconnect(showFire->cancel,SIGNAL(changeClicked()),showFire,SLOT(destroyLabel()));
    disconnect(showFire->ensure,SIGNAL(changeClicked()),showFire,SLOT(sendMessageAskDialog()));
    disconnect(showFire->cancel,SIGNAL(changeClicked()),showFire,SLOT(sendMessageAskDialog()));
    tokenPic = new PicButton(127,568,559,100,42,true,this);
    connect(tokenPic,SIGNAL(changeClicked()),this,SLOT(tokenSet()));
    connect(tokenPic,SIGNAL(notClicked()),this,SLOT(tokenReset()));
    tokenPaint = false;
    tokenNum = 0;
    connect(this,SIGNAL(mouseClick(int,int)),showFire->ensure,SLOT(isThisClicked(int,int)));
    connect(this,SIGNAL(mouseClick(int,int)),showFire->cancel,SLOT(isThisClicked(int,int)));
    for(int i = 0;i < dialog->skillCount;i++)
    {
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    connect(this,SIGNAL(mouseClick(int,int)),tokenPic,SLOT(isThisClicked(int,int)));
    for(int i = 0;i < 2;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),magicGroup[i],SLOT(isThisClicked(int,int)));
    }
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 2;j++)
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
    for(int i = 0;i < 2;i++)
    {
        connect(magicGroup[i],SIGNAL(notClicked()),this,SLOT(skillClear()));
    }
}
void HakureiReimu::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->setChecked(true);
}
void HakureiReimu::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->setChecked(true);
}
void HakureiReimu::changeSelfMode(int mode)
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
            connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
            connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
        }
    }
    cancel->setCheckable(true);
    switch(mode)
    {
        case 4://灵符-雷鸣响应阶段
        case 5://灵符-风行响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            }
            if(mode == 4)
            {
                for(int i = 0;i < cardNum;i++)
                {
                    if(cardList->getNature(card[i]) == thunder)
                    {
                        cardButton[i]->setCheckable(true);
                    }
                }
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    if(cardList->getNature(card[i]) == wind)
                    {
                        cardButton[i]->setCheckable(true);
                    }
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicReset()));
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(elementPlus()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(elementMinus()));
            }
            break;
        }
        case 6://念咒响应阶段
        {
            cancel->setCheckable(true);
            if(tokenNum != 2)
            {
                for(int i = 0;i < cardNum;i++)
                {
                    cardButton[i]->setCheckable(true);
                    connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                    connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 7://百鬼夜行响应阶段
        {
            cancel->setCheckable(true);
            tokenPaint = true;
            for(int i = 0;i < tokenNum;i++)
            {
                tokenButton[i]->setCheckable(true);
                connect(tokenButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(tokenButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                for(int j = 0;j < tokenNum;j++)
                {
                    if(i != j)
                    {
                        connect(tokenButton[i],SIGNAL(changeClicked()),tokenButton[j],SLOT(cancelX()));
                    }
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 8://灵力崩解响应阶段
        {
            emit resetSignal();
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 9://百鬼夜行响应（非火）
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                for(int j = 0;j < 6;j++)
                {
                    if(i != j)
                    {
                        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                    }
                }
            }
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            break;
        }
        case 10://百鬼夜行响应（火）
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(elementPlus()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(elementMinus()));
            }
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            break;
        }
    }
}
//void HakureiReimu::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(showFirePaint)
//    {
//        showFire->paint(event,painter);
//        showFire->labelOne->show();
//    }
//    if(tokenPaint)
//    {
//        for(int i = 0;i < tokenNum;i++)
//        {
//            tokenButton[i]->paint(event,painter);
//            for(int j = 0;j < 5;j++)
//            {
//                tokenButton[i]->label[j]->show();
//            }
//        }
//        for(int i = 0;i < cardNum;i++)
//        {
//            for(int j = 0;j < 5;j++)
//            {
//                cardButton[i]->label[j]->hide();
//            }
//        }
//    }
//    else
//    {
//        for(int i = 0;i < cardNum;i++)
//        {
//            cardButton[i]->paint(event,painter);
//            for(int j = 0;j < 5;j++)
//            {
//                cardButton[i]->label[j]->show();
//            }
//        }
//        for(int i = 0;i < tokenNum;i++)
//        {
//            for(int j = 0;j < 5;j++)
//            {
//                tokenButton[i]->label[j]->hide();
//            }
//        }
//    }
//    if(ask)
//    {
//        dialog->paint(event,painter);
//    }
//    for(int i = 0;i < 2;i++)
//    {
//        magicGroup[i]->paint(event,painter);
//    }
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    tokenPic->paint(event,painter);
//}
void HakureiReimu::setFrame()
{
    ask = true;
    tokenPic->setChecked(false);
    tokenPaint = false;
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setChecked(false);
    }
}*/
void HakureiReimu::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getNature(card[i]) == thunder)
        {
            magicGroup[0]->setCheckable(true);
        }
        if(cardList->getNature(card[i]) == wind)
        {
            magicGroup[1]->setCheckable(true);
        }
    }
}
void HakureiReimu::skillCancel()
{
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicReset()));
    }
    tokenPaint = false;
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->setCheckable(false);
        tokenButton[i]->setChecked(false);
    }
    ask = false;
    showFire->labelOne->hide();
    dialog->label->hide();
    elementCount = 0;
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
    showFire->ensure->setCheckable(false);
    showFire->ensure->setChecked(false);
    showFire->cancel->setCheckable(false);
    showFire->cancel->setChecked(false);
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(elementPlus()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(elementMinus()));
    }
}
void HakureiReimu::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void HakureiReimu::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            changeSelfMode(6 + i);
        }
    }
    dialogReset();
}
void HakureiReimu::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void HakureiReimu::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void HakureiReimu::elementPlus()
{
    elementCount ++;
    if(elementCount == 2)
    {
        ensure->setCheckable(true);
        for(int i = 0;i < 6;i++)
        {
            if(!paintStruct->gameCharacter[i]->characterPic->isChecked())
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
            }
        }
        return;
    }
}
void HakureiReimu::elementMinus()
{
    elementCount --;
    ensure->setCheckable(false);
    for(int i = 0;i < 6;i++)
    {
        paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
    }
}

void HakureiReimu::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            informationKind = 100 + i;
        }
    }
    for(int i = 0;i < 2;i++)
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
        case 100://念咒响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isChecked())
                {
                    token[tokenNum] = card[i];
                    for(int j = 0;j < tokenNum;j++)
                    {
                        delete tokenButton[j];
                    }
                    tokenNum ++;
                    int xOffset = 3;
                    for(int j = 0;j < tokenNum;j++)
                    {
                        tokenButton[j] = new CardButton(token[j],364 + (99 + xOffset) * j,611,windowX);
                        tokenButton[j]->setCheckable(false);
                        tokenButton[j]->setChecked(false);
                        connect(this,SIGNAL(mouseClick(int,int)),tokenButton[j],SLOT(isThisClicked(int,int)));
                    }
                    tempMes.push_back(card[i]);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(3);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 101://百鬼夜行响应阶段
        {
            for(int i = 0;i < 6;i++)
            {
                if(paintStruct->gameCharacter[i]->characterPic->isChecked())
                {
                    break;
                }
                if(i == 5)
                {
                    for(int j = 0;j < tokenNum;j ++)
                    {
                        if(tokenButton[j]->isChecked())
                        {
                            cardRecord = token[j];
                            if(tokenNum == 1)
                            {
                                tokenNum --;
                                delete tokenButton[0];
                            }
                            else
                            {
                                if(j == 1)
                                {
                                    tokenNum --;
                                    delete tokenButton[1];
                                }
                                else
                                {
                                    tokenNum --;
                                    token[0] = token[1];
                                    delete tokenButton[0];
                                    delete tokenButton[1];
                                    tokenButton[0] = new CardButton(token[0],364,611,windowX);
                                    tokenButton[0]->setCheckable(false);
                                    tokenButton[0]->setChecked(false);
                                    connect(this,SIGNAL(mouseClick(int,int)),tokenButton[0],SLOT(isThisClicked(int,int)));
                                }
                            }
                            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
                            ensure->setChecked(false);
                            ensure->setCheckable(false);
                            if(cardList->getNature(cardRecord) == fire)
                            {
                                nightSet();
                            }
                            else
                            {
                                showRecord = false;
                                changeSelfMode(9);
                            }
                            return;
                        }
                        if(j == tokenNum - 1)
                        {
                            tempMes.push_back(4);
                            emit sendMessageSelfSig(tempMes);
                            return;
                        }
                    }
                }
            }
            tempMes.push_back(showRecord);
            putCharacter(tempMes);
            tempMes.push_back(cardRecord);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 102://灵力崩解响应阶段
        {
            tempMes.push_back(5);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://灵符-雷鸣响应阶段
        case 201://灵符-风行响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(informationKind - 199);
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
void HakureiReimu::tokenSet()
{
    storeStatus();
    tokenPaint = true;
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(false);
        cardButton[i]->setChecked(false);
    }
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
    showFirePaint = false;
    showFire->ensure->setCheckable(false);
    showFire->ensure->setChecked(false);
    showFire->cancel->setCheckable(false);
    showFire->cancel->setChecked(false);
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
    ensure->setCheckable(false);
    ensure->setChecked(false);
    cancel->setCheckable(false);
    cancel->setChecked(false);
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->setCheckable(false);
        tokenButton[i]->setChecked(false);
    }
}
void HakureiReimu::tokenReset()
{
    reStore();
}
void HakureiReimu::reStore()
{
    tokenPaint = storeArray[0];
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(storeArray[1 + i * 2]);
        cardButton[i]->setChecked(storeArray[2 + i * 2]);
    }
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->setCheckable(storeArray[31 + i * 2]);
        magicGroup[i]->setChecked(storeArray[32 + i * 2]);
    }
    showFirePaint = storeArray[35];
    showFire->ensure->setCheckable(storeArray[36]);
    showFire->ensure->setChecked(storeArray[37]);
    showFire->cancel->setCheckable(storeArray[38]);
    showFire->cancel->setChecked(storeArray[39]);
    ask = storeArray[40];
    if(ask)
    {
        dialog->label->show();
    }
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(storeArray[41 + i * 2]);
        dialog->skillGroup[i]->setChecked(storeArray[42 + i * 2]);
    }
    ensure->setCheckable(storeArray[47]);
    ensure->setChecked(storeArray[48]);
    cancel->setCheckable(storeArray[49]);
    cancel->setChecked(storeArray[50]);
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->setCheckable(storeArray[51 + i * 2]);
        tokenButton[i]->setChecked(storeArray[52 + i * 2]);
    }
}
void HakureiReimu::storeStatus()
{
    storeArray[0] = tokenPaint;
    for(int i = 0;i < cardNum;i++)
    {
        storeArray[1 + i * 2] = cardButton[i]->isCheckable();
        storeArray[2 + i * 2] = cardButton[i]->isChecked();
    }
    for(int i = 0;i < 2;i++)
    {
        storeArray[31 + i * 2] = magicGroup[i]->isCheckable();
        storeArray[32 + i * 2] = magicGroup[i]->isChecked();
    }
    storeArray[35] = showFirePaint;
    storeArray[36] = showFire->ensure->isCheckable();
    storeArray[37] = showFire->ensure->isChecked();
    storeArray[38] = showFire->cancel->isCheckable();
    storeArray[39] = showFire->cancel->isChecked();
    storeArray[40] = ask;
    if(ask)
    {
        dialog->label->hide();
    }
    for(int i = 0;i < dialog->skillCount;i++)
    {
        storeArray[41 + i * 2] = dialog->skillGroup[i]->isCheckable();
        storeArray[42 + i * 2] = dialog->skillGroup[i]->isChecked();
    }
    storeArray[47] = ensure->isCheckable();
    storeArray[48]= ensure->isChecked();
    storeArray[49] = cancel->isCheckable();
    storeArray[50] = cancel->isChecked();
    for(int i = 0;i < tokenNum;i++)
    {
        storeArray[51 + i * 2] = tokenButton[i]->isCheckable();
        storeArray[52 + i * 2] = tokenButton[i]->isChecked();
    }
}
void HakureiReimu::nightSet()
{
    showFirePaint = true;
    showFire->ensure->setCheckable(true);
    showFire->cancel->setCheckable(true);
}
void HakureiReimu::fireChoose()
{
    showRecord = true;
    showFirePaint = false;
    showFire->ensure->setCheckable(false);
    showFire->cancel->setCheckable(false);
    showFire->labelOne->hide();
    changeSelfMode(10);
}
void HakureiReimu::fireNotChoose()
{
    showRecord = false;
    showFirePaint = false;
    showFire->ensure->setCheckable(false);
    showFire->cancel->setCheckable(false);
    showFire->labelOne->hide();
    changeSelfMode(9);
}
void HakureiReimu::magicReset()
{
    elementCount = 0;
    ensure->setCheckable(false);
}
