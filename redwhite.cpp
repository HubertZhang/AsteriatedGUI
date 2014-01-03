#include "redwhite.h"

RedWhite::RedWhite(PaintStruct* paintStruct,QWidget *parent,Window* bloodX):
    CardAndSkill(paintStruct,parent)
{
    lifeLinkCha = -1;
    bloodAsk = false;
    bloodCount = 0;
    curseCount = 0;
    curseLine = 0;
    lifeLink = false;
    int info[3] = {2,0,0};
    blood = new AskDialog(info,bloodX,paintStructX,false);
    blood->ensure->canBeClicked = false;
    blood->cancel->canBeClicked = false;
    blood->ensure->isClicked = false;
    blood->cancel->isClicked = false;
    for(int i = 0;i < 5;i++)
    {
        blood->number[i]->isClicked = false;
        blood->number[i]->canBeClicked = false;
    }
    connect(blood->ensure,SIGNAL(changeClicked()),this,SLOT(sendMessageCardAndSkill()));
    connect(blood->cancel,SIGNAL(changeClicked()),this,SLOT(sendMessageCardAndSkill()));
    disconnect(blood->ensure,SIGNAL(changeClicked()),blood,SLOT(destroyLabel()));
    disconnect(blood->cancel,SIGNAL(changeClicked()),blood,SLOT(destroyLabel()));
    connect(blood->ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
    connect(blood->cancel,SIGNAL(changeClicked()),this,SLOT(reset()));
    magicGroup[0] = new PicButton(151,362,559,100,42,false);
    magicGroup[1] = new PicButton(154,465,559,100,42,false);
    magicGroup[2] = new PicButton(155,568,559,100,42,false);
    magicGroup[3] = new PicButton(156,671,559,100,42,false);
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
void RedWhite::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void RedWhite::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(7);
    magicGroup[1]->isClicked = true;
}
void RedWhite::magicSetTwo()
{
    linkReset();
    skillset();
    changeSelfMode(8);
    magicGroup[2]->isClicked = true;
}
void RedWhite::magicSetThree()
{
    linkReset();
    skillset();
    changeSelfMode(9);
    magicGroup[3]->isClicked = true;
}
void RedWhite::changeSelfMode(int mode)
{
    switch(mode)
    {
        case 4://同生共死响应阶段
        {
            clickAllSet();
            singleToEnsure();
            break;
        }
        case 7://逆流响应阶段
        {
            cardSetOne();
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(bloodPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(bloodMinus()));
            }
            break;
        }
        case 8://血之悲鸣响应阶段
        {
            cardSingleSet(231);
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(clickAllSet()));
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(singleToEnsure()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(allReset()));
            }
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(bloodSet()));
            break;
        }
        case 9://血之诅咒响应阶段
        {
            cardSetOne();
            if(cardNum > 2)
            {
                curseLine = 3;
            }
            else
            {
                curseLine = cardNum;
                if(!cardNum)
                {
                    clickAllSet();
                    singleToEnsure();
                    return;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(cursePlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(curseMinus()));
            }
            break;
        }
        case 10://血之悲鸣响应二阶段
        {
            bloodAsk = true;
            blood->ensure->canBeClicked = false;
            for(int i = 0;i < 5;i++)
            {
                if(i < 3)
                {
                    blood->number[i]->canBeClicked = true;
                }
                else
                {
                    blood->number[i]->canBeClicked = false;
                }
            }
            break;
        }
    }
}
void RedWhite::paint(QPaintEvent *event, QPainter *painter)
{
    if(bloodAsk)
    {
        blood->paint(event,painter);
    }
    for(int i = 0;i < 4;i++)
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
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->isClicked = false;
    }
}*/
void RedWhite::skillset()
{
    if(!lifeLink)
    {
        magicGroup[0]->canBeClicked = true;
    }
    if(paintStructX->gameCharacter[5]->activated)
    {
        magicGroup[1]->canBeClicked = true;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillTwo(card[i]) == 231 && paintStructX->gameCharacter[5]->isActivated)
        {
            magicGroup[2]->canBeClicked = true;
        }
    }
    if(paintStructX->gameCharacter[5]->gem > 0)
    {
        magicGroup[3]->canBeClicked = true;
    }
}
void RedWhite::skillCancel()
{
    bloodAsk = false;
    bloodCount = 0;
    curseCount = 0;
    blood->labelOne->hide();
    blood->labelTwo->hide();
    for(int i = 0;i < 4;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
    blood->ensure->canBeClicked = false;
    blood->cancel->canBeClicked = false;
    blood->ensure->isClicked = false;
    blood->cancel->isClicked = false;
    for(int i = 0;i < 5;i++)
    {
        blood->number[i]->isClicked = false;
        blood->number[i]->canBeClicked = false;
    }
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(clickAllSet()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(singleToEnsure()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(allReset()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(cursePlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(curseMinus()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(bloodPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(bloodMinus()));
    }
    disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(bloodSet()));
}
void RedWhite::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void RedWhite::sendMessageSelf()
{
    for(int i = 0;i < 4;i++)
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
        case 6://血之哀伤
        {
            putCharacter(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://同生共死
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            putCharacter(tempMes);
            lifeLink = true;
            for(int i = 0;i < 6;i++)
            {
                if(paintStructX->gameCharacter[i]->characterPic->isClicked)
                {
                    lifeLinkCha = i;
                }
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://逆流
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            putCardCount(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 202://血之悲鸣响应阶段
        {
        //system("pause");
            if(!bloodAsk)
            {
                tempMes.push_back(1);
                tempMes.push_back(3);
                putCharacter(tempMes);
                putCard(tempMes);
                emit sendMessageSelfSig(tempMes);
                return;
            }
            else
            {
                for(int i = 0;i < 5;i++)
                {
                    if(blood->number[i]->isClicked)
                    {
                        tempMes.push_back(i + 1);
                        emit sendMessageSelfSig(tempMes);
                        return;
                    }
                }
            }

        }
        case 203://血之诅咒响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
            putCharacter(tempMes);
            putCardCount(tempMes);
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
void RedWhite::bloodPlus()
{
    bloodCount ++;
    if(bloodCount == 2)
    {
        cardResetOne();
        ensure->canBeClicked = true;
    }
}
void RedWhite::bloodMinus()
{
    bloodCount --;
    cardSetOne();
    ensure->canBeClicked = false;
}
void RedWhite::cursePlus()
{
    curseCount ++;
    if(curseCount == curseLine)
    {
        clickAllSet();
        singleToEnsure();
        cardResetOne();
    }
}
void RedWhite::curseMinus()
{
    curseCount --;
    cardSetOne();
    allReset();
    ensure->canBeClicked = false;
}
bool RedWhite::redWhiteLink()
{
    return lifeLink;
}
void RedWhite::lifeLinkOver()
{
    lifeLink = false;
    lifeLinkCha = -1;
}
void RedWhite::clickRedWhiteSet()
{
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if(i != j)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
        if(i != lifeLinkCha)
        {
            paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
        }
    }
}
void RedWhite::bloodSet()
{
    changeSelfMode(10);
}
