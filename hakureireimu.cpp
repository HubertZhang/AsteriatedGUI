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
    magicGroup[0] = new PicButton(122,362,559,100,42,false);
    magicGroup[1] = new PicButton(123,465,559,100,42,false);
    int info[3] = {0,0,0};
    showFirePaint = false;
    showFire = new AskDialog(info,showX,paintStruct);
    showFire->labelOne->hide();
    showFire->labelOne->setText("展示火系");
    showFire->labelTwo->setText("");
    showFire->ensure->canBeClicked = false;
    showFire->cancel->canBeClicked = false;
    connect(showFire->ensure,SIGNAL(changeClicked()),this,SLOT(fireChoose()));
    connect(showFire->cancel,SIGNAL(changeClicked()),this,SLOT(fireNotChoose()));
    disconnect(showFire->ensure,SIGNAL(changeClicked()),showFire,SLOT(destroyLabel()));
    disconnect(showFire->cancel,SIGNAL(changeClicked()),showFire,SLOT(destroyLabel()));
    disconnect(showFire->ensure,SIGNAL(changeClicked()),showFire,SLOT(sendMessageAskDialog()));
    disconnect(showFire->cancel,SIGNAL(changeClicked()),showFire,SLOT(sendMessageAskDialog()));
    tokenPic = new PicButton(127,568,559,100,42,true);
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
    magicGroup[0]->isClicked = true;
}
void HakureiReimu::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
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
            connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
            connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
        }
    }
    cancel->canBeClicked = true;
    switch(mode)
    {
        case 4://灵符-雷鸣响应阶段
        case 5://灵符-风行响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
            }
            if(mode == 4)
            {
                for(int i = 0;i < cardNum;i++)
                {
                    if(cardList->getNature(card[i]) == thunder)
                    {
                        cardButton[i]->canBeClicked = true;
                    }
                }
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    if(cardList->getNature(card[i]) == wind)
                    {
                        cardButton[i]->canBeClicked = true;
                    }
                }
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(elementPlus()));
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(elementMinus()));
            }
            break;
        }
        case 6://念咒响应阶段
        {
            cancel->canBeClicked = true;
            if(tokenNum != 2)
            {
                for(int i = 0;i < cardNum;i++)
                {
                    cardButton[i]->canBeClicked = true;
                    connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                    connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 7://百鬼夜行响应阶段
        {
            cancel->canBeClicked = true;
            tokenPaint = true;
            for(int i = 0;i < tokenNum;i++)
            {
                tokenButton[i]->canBeClicked = true;
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
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                for(int j = 0;j < 6;j++)
                {
                    if(i != j)
                    {
                        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
                    }
                }
            }
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            break;
        }
        case 10://百鬼夜行响应（火）
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(elementPlus()));
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(elementMinus()));
            }
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            break;
        }
    }
}
void HakureiReimu::paint(QPaintEvent *event, QPainter *painter)
{
    if(showFirePaint)
    {
        showFire->paint(event,painter);
        showFire->labelOne->show();
    }
    if(tokenPaint)
    {
        for(int i = 0;i < tokenNum;i++)
        {
            tokenButton[i]->paint(event,painter);
            for(int j = 0;j < 5;j++)
            {
                tokenButton[i]->label[j]->show();
            }
        }
        for(int i = 0;i < cardNum;i++)
        {
            for(int j = 0;j < 5;j++)
            {
                cardButton[i]->label[j]->hide();
            }
        }
    }
    else
    {
        for(int i = 0;i < cardNum;i++)
        {
            cardButton[i]->paint(event,painter);
            for(int j = 0;j < 5;j++)
            {
                cardButton[i]->label[j]->show();
            }
        }
        for(int i = 0;i < tokenNum;i++)
        {
            for(int j = 0;j < 5;j++)
            {
                tokenButton[i]->label[j]->hide();
            }
        }
    }
    if(ask)
    {
        dialog->paint(event,painter);
    }
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->paint(event,painter);
    }
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    tokenPic->paint(event,painter);
}
void HakureiReimu::setFrame()
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
void HakureiReimu::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getNature(card[i]) == thunder)
        {
            magicGroup[0]->canBeClicked = true;
        }
        if(cardList->getNature(card[i]) == wind)
        {
            magicGroup[1]->canBeClicked = true;
        }
    }
}
void HakureiReimu::skillCancel()
{
    tokenPaint = false;
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->canBeClicked = false;
        tokenButton[i]->isClicked = false;
    }
    ask = false;
    showFire->labelOne->hide();
    dialog->label->hide();
    elementCount = 0;
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
    showFire->ensure->canBeClicked = false;
    showFire->ensure->isClicked = false;
    showFire->cancel->canBeClicked = false;
    showFire->cancel->isClicked = false;
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(elementPlus()));
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(elementMinus()));
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
        if(dialog->skillGroup[i]->isClicked)
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
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
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
        ensure->canBeClicked = true;
        for(int i = 0;i < 6;i++)
        {
            if(!paintStructX->gameCharacter[i]->characterPic->isClicked)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = false;
            }
        }
        return;
    }
}
void HakureiReimu::elementMinus()
{
    elementCount --;
    ensure->canBeClicked = false;
    for(int i = 0;i < 6;i++)
    {
        paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
    }
}

void HakureiReimu::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            informationKind = 100 + i;
        }
    }
    for(int i = 0;i < 2;i++)
    {
        if(magicGroup[i]->isClicked)
        {
            informationKind = 200 + i;
        }
    }
    std::vector<int> tempMes;
    if(cancel->isClicked && informationKind < 100)
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
    if(cancel->isClicked && informationKind > 99 && !ensure->canBeClicked)
    {
        tempMes.push_back(-1);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    if(cancel->isClicked && informationKind > 99 && ensure->canBeClicked)
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
                if(cardButton[i]->isClicked)
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
                        tokenButton[j] = new CardButton(48,364 + (99 + xOffset) * j,611,99,143,false,token[j],windowX);
                        tokenButton[j]->canBeClicked = false;
                        tokenButton[j]->isClicked = false;
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
                if(paintStructX->gameCharacter[i]->characterPic->isClicked)
                {
                    break;
                }
                if(i == 5)
                {
                    for(int j = 0;j < tokenNum;j ++)
                    {
                        if(tokenButton[j]->isClicked)
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
                                    tokenButton[0] = new CardButton(48,364,611,99,143,false,token[0],windowX);
                                    tokenButton[0]->canBeClicked = false;
                                    tokenButton[0]->isClicked = false;
                                    connect(this,SIGNAL(mouseClick(int,int)),tokenButton[0],SLOT(isThisClicked(int,int)));
                                }
                            }
                            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
                            ensure->isClicked = false;
                            ensure->canBeClicked = false;
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
        cardButton[i]->canBeClicked = false;
        cardButton[i]->isClicked = false;
    }
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
    showFirePaint = false;
    showFire->ensure->canBeClicked = false;
    showFire->ensure->isClicked = false;
    showFire->cancel->canBeClicked = false;
    showFire->cancel->isClicked = false;
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
    ensure->canBeClicked = false;
    ensure->isClicked = false;
    cancel->canBeClicked = false;
    cancel->isClicked = false;
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->canBeClicked = false;
        tokenButton[i]->isClicked = false;
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
        cardButton[i]->canBeClicked = storeArray[1 + i * 2];
        cardButton[i]->isClicked = storeArray[2 + i * 2];
    }
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->canBeClicked = storeArray[31 + i * 2];
        magicGroup[i]->isClicked = storeArray[32 + i * 2];
    }
    showFirePaint = storeArray[35];
    showFire->ensure->canBeClicked = storeArray[36];
    showFire->ensure->isClicked = storeArray[37];
    showFire->cancel->canBeClicked = storeArray[38];
    showFire->cancel->isClicked = storeArray[39];
    ask = storeArray[40];
    if(ask)
    {
        dialog->label->show();
    }
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = storeArray[41 + i * 2];
        dialog->skillGroup[i]->isClicked = storeArray[42 + i * 2];
    }
    ensure->canBeClicked = storeArray[47];
    ensure->isClicked = storeArray[48];
    cancel->canBeClicked = storeArray[49];
    cancel->isClicked = storeArray[50];
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->canBeClicked = storeArray[51 + i * 2];
        tokenButton[i]->isClicked = storeArray[52 + i * 2];
    }
}
void HakureiReimu::storeStatus()
{
    storeArray[0] = tokenPaint;
    for(int i = 0;i < cardNum;i++)
    {
        storeArray[1 + i * 2] = cardButton[i]->canBeClicked;
        storeArray[2 + i * 2] = cardButton[i]->isClicked;
    }
    for(int i = 0;i < 2;i++)
    {
        storeArray[31 + i * 2] = magicGroup[i]->canBeClicked;
        storeArray[32 + i * 2] = magicGroup[i]->isClicked;
    }
    storeArray[35] = showFirePaint;
    storeArray[36] = showFire->ensure->canBeClicked;
    storeArray[37] = showFire->ensure->isClicked;
    storeArray[38] = showFire->cancel->canBeClicked;
    storeArray[39] = showFire->cancel->isClicked;
    storeArray[40] = ask;
    if(ask)
    {
        dialog->label->hide();
    }
    for(int i = 0;i < dialog->skillCount;i++)
    {
        storeArray[41 + i * 2] = dialog->skillGroup[i]->canBeClicked;
        storeArray[42 + i * 2] = dialog->skillGroup[i]->isClicked;
    }
    storeArray[47] = ensure->canBeClicked;
    storeArray[48]= ensure->isClicked;
    storeArray[49] = cancel->canBeClicked;
    storeArray[50] = cancel->isClicked;
    for(int i = 0;i < tokenNum;i++)
    {
        storeArray[51 + i * 2] = tokenButton[i]->canBeClicked;
        storeArray[52 + i * 2] = tokenButton[i]->isClicked;
    }
}
void HakureiReimu::nightSet()
{
    showFirePaint = true;
    showFire->ensure->canBeClicked = true;
    showFire->cancel->canBeClicked = true;
}
void HakureiReimu::fireChoose()
{
    showRecord = true;
    showFirePaint = false;
    showFire->ensure->canBeClicked = false;
    showFire->cancel->canBeClicked = false;
    showFire->labelOne->hide();
    changeSelfMode(10);
}
void HakureiReimu::fireNotChoose()
{
    showRecord = false;
    showFirePaint = false;
    showFire->ensure->canBeClicked = false;
    showFire->cancel->canBeClicked = false;
    showFire->labelOne->hide();
    changeSelfMode(9);
}
