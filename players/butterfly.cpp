#include "butterfly.h"

Butterfly::Butterfly(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    confuseCount = 0;
    deadflyCount = 0;
    cryCount = 0;
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(24);//毒粉,朝圣,镜花水月,凋零
    magicGroup[0] = new PicButton(157,362,559,100,42,false);
    magicGroup[1] = new PicButton(162,465,559,100,42,false);
    magicGroup[2] = new PicButton(163,568,559,100,42,false);
    tokenPic = new PicButton(164,671,559,100,42,true);
    connect(tokenPic,SIGNAL(changeClicked()),this,SLOT(tokenSet()));
    connect(tokenPic,SIGNAL(notClicked()),this,SLOT(tokenReset()));
    tokenPaint = false;
    tokenNum = 0;
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
    connect(this,SIGNAL(mouseClick(int,int)),this,SLOT(tokenClicked(int,int)));
    connect(this,SIGNAL(mouseClick(int,int)),tokenPic,SLOT(isThisClicked(int,int)));
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
void Butterfly::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void Butterfly::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(9);
    magicGroup[1]->isClicked = true;
}
void Butterfly::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(10);
    magicGroup[2]->isClicked = true;
}

void Butterfly::changeSelfMode(int mode)
{
    switch(mode)
    {
        case 4://舞动响应阶段
        {
            ensure->canBeClicked = true;
            cardSingleSet(-1);
            break;
        }
        case 5://毒粉响应阶段
        case 6://朝圣响应阶段
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
        case 7://镜花水月响应阶段
        {
            cancel->canBeClicked = true;
            tokenPaint = true;
            for(int i = 0;i < tokenNum;i++)
            {
                tokenButton[i]->canBeClicked = true;
                connect(tokenButton[i],SIGNAL(changeClicked()),this,SLOT(confusePlus()));
                connect(tokenButton[i],SIGNAL(notClicked()),this,SLOT(confuseMinus()));
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 8://凋零响应阶段
        {
            clickAllSet();
            singleToEnsure();
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 9://蛹化响应阶段
        {
            ensure->canBeClicked = true;
            break;
        }
        case 10://倒逆之蝶响应阶段
        {
            cardSetOne();
            if(!cardNum)
            {
                ensure->canBeClicked = true;
                clickAllSet();
                break;
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(deadflyPlus()));
                    connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(deadflyMinus()));
                }
                if(cardNum == 1)
                {
                    cryCount = 1;
                }
                else
                {
                    cryCount = 2;
                }
            }
            break;
        }
    }
}
void Butterfly::paint(QPaintEvent *event, QPainter *painter)
{
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
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->paint(event,painter);
    }
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    tokenPic->paint(event,painter);
}
void Butterfly::setFrame()
{
    ask = true;
    tokenPic->isClicked = false;
    tokenPaint = false;
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->isClicked = false;
    }
}*/
void Butterfly::skillset()
{
    magicGroup[0]->canBeClicked = true;
    if(paintStructX->gameCharacter[5]->gem != 0)
    {
        magicGroup[1]->canBeClicked = true;
        magicGroup[2]->canBeClicked = true;
    }
    if(paintStructX->gameCharacter[5]->crystal != 0)
    {
        magicGroup[2]->canBeClicked = true;
    }
}
void Butterfly::skillCancel()
{
    tokenPaint = false;
    confuseCount = 0;
    deadflyCount = 0;
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->canBeClicked = false;
        tokenButton[i]->isClicked = false;
    }
    ask = false;
    dialog->label->hide();
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
    for(int i = 0;i < tokenNum;i++)
    {
        disconnect(tokenButton[i],SIGNAL(changeClicked()),this,SLOT(confusePlus()));
        disconnect(tokenButton[i],SIGNAL(notClicked()),this,SLOT(confuseMinus()));
    }
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(deadflyPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(deadflyMinus()));
    }
}
void Butterfly::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void Butterfly::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            changeSelfMode(5 + i);
        }
    }
    dialogReset();
}
void Butterfly::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void Butterfly::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void Butterfly::confusePlus()
{
    confuseCount ++;
    if(confuseCount == 2)
    {
        ensure->canBeClicked = true;
        for(int i = 0;i < tokenNum;i++)
        {
            if(!tokenButton[i]->isClicked)
            {
                tokenButton[i]->canBeClicked = false;
            }
        }
        return;
    }
    if(confuseCount == 1)
    {
        int attribute = -1;
        for(int i = 0;i < tokenNum;i++)
        {
            if(tokenButton[i]->isClicked)
            {
                attribute = cardList->getNature(token[i]);
            }
        }
        for(int i = 0;i < tokenNum;i++)
        {
            if(cardList->getNature(token[i]) == attribute)
            {
                tokenButton[i]->canBeClicked = true;
            }
            else
            {
                tokenButton[i]->canBeClicked = false;
            }
        }
        return;
    }
}
void Butterfly::confuseMinus()
{
    ensure->canBeClicked = false;
    confuseCount --;
    if(confuseCount == 1)
    {
        int attribute = -1;
        for(int i = 0;i < tokenNum;i++)
        {
            if(tokenButton[i]->isClicked)
            {
                attribute = cardList->getNature(token[i]);
            }
            if(cardList->getNature(token[i]) == attribute)
            {
                tokenButton[i]->canBeClicked = true;
            }
            else
            {
                tokenButton[i]->canBeClicked = false;
            }
        }
        return;
    }
    else
    {
        for(int i = 0;i < tokenNum;i++)
        {
            tokenButton[i]->canBeClicked = true;
        }
    }
}

void Butterfly::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            informationKind = 100 + i;
        }
    }
    for(int i = 0;i < 3;i++)
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
        case 100://毒粉响应阶段
        case 101://朝圣响应阶段
        case 102://镜花水月响应阶段
        {
            tempMes.push_back(informationKind - 98);
            for(int i = 0;i < tokenNum;i++)
            {
                if(tokenButton[i]->isClicked)
                {
                    tempMes.push_back(token[i]);
                }
            }
            int tokenCount = 0;
            for(int i = 0;i < tokenNum;i++)
            {
                if(!tokenButton[i]->isClicked)
                {
                    token[tokenCount] = token[i];
                    tokenCount ++;
                }
                delete tokenButton[i];
            }
            tokenNum = tokenCount;
            int xOffset = 3;
            for(int i = 0;i < tokenNum;i ++)
            {
                if(tokenNum < 7)
                {
                    tokenButton[i] = new CardButton(48,364 + (99 + xOffset) * i,611,99,143,false,token[i],windowX);
                }
                else
                {
                    xOffset = ((102 * 6) - 99)/(tokenNum - 1);
                    tokenButton[i] = new CardButton(48,364 + xOffset * i,611,99,143,false,token[i],windowX);
                }
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 103://凋零响应阶段
        {
            tempMes.push_back(5);
            putCharacter(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://舞动响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    tempMes.push_back(0);
                    tempMes.push_back(card[i]);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://蛹化响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(6);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 202://倒逆之蝶响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(7);
            putCardCount(tempMes);
            putCard(tempMes);
            for(int i = 0;i < 6;i++)
            {
                if(paintStructX->gameCharacter[i]->characterPic->isClicked)
                {
                    if(i != 5)
                    {
                        tempMes.push_back(1);
                        putCharacter(tempMes);
                    }
                    else
                    {
                        tempMes.push_back(3);
                    }
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
void Butterfly::tokenSet()
{
    storeStatus();
    tokenPaint = true;
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->canBeClicked = false;
        cardButton[i]->isClicked = false;
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
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
void Butterfly::tokenReset()
{
    reStore();
}
void Butterfly::reStore()
{
    tokenPaint = storeArray[0];
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->canBeClicked = storeArray[1 + i * 2];
        cardButton[i]->isClicked = storeArray[2 + i * 2];
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = storeArray[31 + i * 2];
        magicGroup[i]->isClicked = storeArray[32 + i * 2];
    }
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
    ensure->canBeClicked = storeArray[49];
    ensure->isClicked = storeArray[50];
    cancel->canBeClicked = storeArray[51];
    cancel->isClicked = storeArray[52];
    for(int i = 0;i < tokenNum;i++)
    {
        tokenButton[i]->canBeClicked = storeArray[53 + i * 2];
        tokenButton[i]->isClicked = storeArray[54 + i * 2];
    }
}
void Butterfly::storeStatus()
{
    storeArray[0] = tokenPaint;
    for(int i = 0;i < cardNum;i++)
    {
        storeArray[1 + i * 2] = cardButton[i]->canBeClicked;
        storeArray[2 + i * 2] = cardButton[i]->isClicked;
    }
    for(int i = 0;i < 3;i++)
    {
        storeArray[31 + i * 2] = magicGroup[i]->canBeClicked;
        storeArray[32 + i * 2] = magicGroup[i]->isClicked;
    }
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
    storeArray[49] = ensure->canBeClicked;
    storeArray[50]= ensure->isClicked;
    storeArray[51] = cancel->canBeClicked;
    storeArray[52] = cancel->isClicked;
    for(int i = 0;i < tokenNum;i++)
    {
        storeArray[53 + i * 2] = tokenButton[i]->canBeClicked;
        storeArray[54 + i * 2] = tokenButton[i]->isClicked;
    }
}
void Butterfly::tokenClicked(int x, int y)
{
    if(x > 364 && x < 976)
    {
        if(y > 611 && y < 754)
        {
            if(tokenNum < 7)
            {
                int i = ((x - 364)/102);
                if(i > tokenNum - 1)
                {
                    return;
                }
                else
                {
                    tokenButton[i]->isThisClicked(x,y);
                }
            }
            else
            {
                if(x > (976 - 99))
                {
                    int x = tokenButton[tokenNum - 1]->xp + 50;
                    int y = tokenButton[tokenNum - 1]->yp + 50;
                    tokenButton[tokenNum - 1]->isThisClicked(x,y);
                }
                else
                {
                    int i = (x - 364)/(((102 * 6) - 99)/(tokenNum - 1));
                    int x = tokenButton[i]->xp + 50;
                    int y = tokenButton[i]->yp + 50;
                    tokenButton[i]->isThisClicked(x,y);
                }
            }
        }
    }
}
void Butterfly::deadflyPlus()
{
    deadflyCount ++;
    if(deadflyCount == cryCount)
    {
        ensure->canBeClicked = true;
        cardResetOne();
        clickAllSet();
    }
}
void Butterfly::deadflyMinus()
{
    deadflyCount --;
    ensure->canBeClicked = false;
    allReset();
    characterDisconnect();
    cardSetOne();
}
void Butterfly::butterflyTokenAdd(int tokenX[15])
{
    for(int i = 0;i < tokenNum;i++)
    {
        delete tokenButton[i];
    }
    for(int i = 0;i < tokenX[1];i++)
    {
        token[tokenNum] = tokenX[2 + i];
        tokenNum ++;
    }
    int xOffset = 3;
    for(int i = 0;i < tokenNum;i ++)
    {
        if(tokenNum < 7)
        {
            tokenButton[i] = new CardButton(48,364 + (99 + xOffset) * i,611,99,143,false,token[i],windowX);
        }
        else
        {
            xOffset = ((102 * 6) - 99)/(tokenNum - 1);
            tokenButton[i] = new CardButton(48,364 + xOffset * i,611,99,143,false,token[i],windowX);
        }
    }
}
