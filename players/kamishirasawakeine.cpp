#include "kamishirasawakeine.h"

KamishirasawaKeine::KamishirasawaKeine(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(17);//法术反弹
    magicGroup[0] = new PicButton(120,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(121,465,559,100,42,false,this);
    for(int i = 0;i < dialog->skillCount;i++)
    {
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
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
void KamishirasawaKeine::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(5);
    magicGroup[0]->setChecked(true);
}
void KamishirasawaKeine::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[1]->setChecked(true);
}
void KamishirasawaKeine::changeSelfMode(int mode)
{
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->setCheckable(true);
    }
    cancel->setCheckable(true);
    switch(mode)
    {
        case 4://法术反弹响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(magicRespondPlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicRespondMinus()));
            }
            break;
        }
        case 5://魔道法典响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(magicCodePlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicCodeMinus()));
            }
            break;
        }
        case 6://圣洁法典响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(sacredCodePlus()));
                connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(sacredCodeMinus()));
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(sacredCodeCharacterSet()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(sacredCodeCharacterSet()));
            }
            break;
        }
    }
}
//void KamishirasawaKeine::paint(QPaintEvent *event, QPainter *painter)
//{
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
//    for(int i = 0;i < cardNum;i++)
//    {
//        cardButton[i]->paint(event,painter);
//    }
//}
void KamishirasawaKeine::setFrame()
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
void KamishirasawaKeine::skillset()
{
    bool magicC = false;
    bool sacredC = false;
    int natureCount[7];
    for(int i = 0;i < 7;i++)
    {
        natureCount[i] = 0;
    }
    for(int i = 0;i < cardNum;i++)
    {
        natureCount[cardList->getNature(card[i])] = 1;
    }
    int differentCount = 0;
    for(int i = 0;i < 7;i++)
    {
        differentCount += natureCount[i];
    }
    if(differentCount > 1)
    {
        magicC = true;
    }
    if(differentCount > 2)
    {
        sacredC = true;
    }
    magicGroup[0]->setCheckable(magicC);
    magicGroup[1]->setCheckable(sacredC);
    if(!paintStruct->gameCharacter[5]->gem)
    {
        magicGroup[0]->setCheckable(false);
        magicGroup[1]->setCheckable(false);
    }
}
void KamishirasawaKeine::skillCancel()
{
    ask = false;
    dialog->label->hide();
    magicCodeCount = 0;
    sacredCodeCount = 0;
    magicRespondCount = 0;
    for(int i = 0;i < cardNum;i++)
    {
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(magicRespondPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicRespondMinus()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(magicCodePlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(magicCodeMinus()));
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(sacredCodePlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(sacredCodeMinus()));
    }
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(sacredCodeCharacterSet()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(sacredCodeCharacterSet()));
    }
    for(int i = 0;i < 2;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
}
void KamishirasawaKeine::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void KamishirasawaKeine::selfReset()
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
void KamishirasawaKeine::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void KamishirasawaKeine::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void KamishirasawaKeine::magicRespondPlus()
{
    if(!magicRespondCount)
    {
        magicRespondCount ++;
        int attribute = 0;
        for(int i = 0;i < cardNum;i++)
        {
            if(cardButton[i]->isChecked())
            {
                attribute = cardList->getNature(card[i]);
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
    else
    {
        magicRespondCount ++;
        for(int i = 0;i < 6;i++)
        {
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 6;j++)
            {
                if(i != j)
                {
                    disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                }
            }
        }
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
    }
}
void KamishirasawaKeine::magicRespondMinus()
{
    if(magicRespondCount == 1)
    {
        magicRespondCount --;
        for(int i = 0;i < cardNum;i++)
        {
            cardButton[i]->setCheckable(true);
        }
        return;
    }
    if(magicRespondCount == 2)
    {
        magicRespondCount --;
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 6;j++)
            {
                if(i != j)
                {
                    disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                }
            }
        }
        return;
    }
    magicRespondCount --;
}
void KamishirasawaKeine::magicCodePlus()
{
    magicCodeCount ++;
    bool natureCount[7];
    for(int i = 0;i < 7;i++)
    {
        natureCount[i] = false;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            natureCount[cardList->getNature(card[i])] = true;
        }
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(natureCount[cardList->getNature(card[i])] && !cardButton[i]->isChecked())
        {
            cardButton[i]->setCheckable(false);
        }
        else
        {
            cardButton[i]->setCheckable(true);
        }
    }
    if(magicCodeCount > 1)
    {
        for(int i = 0;i < 6;i++)
        {
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 6;j++)
            {
                if(i != j)
                {
                    disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                }
            }
        }
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
    }
}
void KamishirasawaKeine::magicCodeMinus()
{
    magicCodeCount --;
    bool natureCount[7];
    for(int i = 0;i < 7;i++)
    {
        natureCount[i] = false;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            natureCount[cardList->getNature(card[i])] = true;
        }
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(natureCount[cardList->getNature(card[i])] && !cardButton[i]->isChecked())
        {
            cardButton[i]->setCheckable(false);
        }
        else
        {
            cardButton[i]->setCheckable(true);
        }
    }
    if(magicCodeCount == 1)
    {
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 6;j++)
            {
                if(i != j)
                {
                    disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                }
            }
        }
    }
}
void KamishirasawaKeine::sacredCodePlus()
{
    int characterCount = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            characterCount ++;
        }
    }
    sacredCodeCount ++;
    bool natureCount[7];
    for(int i = 0;i < 7;i++)
    {
        natureCount[i] = false;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            natureCount[cardList->getNature(card[i])] = true;
        }
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(natureCount[cardList->getNature(card[i])] && !cardButton[i]->isChecked())
        {
            cardButton[i]->setCheckable(false);
        }
        else
        {
            cardButton[i]->setCheckable(true);
        }
    }
    if(sacredCodeCount > characterCount + 2)
    {
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        }
    }
}
void KamishirasawaKeine::sacredCodeMinus()
{
    //system("pause");
    int characterCount = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            characterCount ++;
        }
    }
    sacredCodeCount --;
    bool natureCount[7];
    for(int i = 0;i < 7;i++)
    {
        natureCount[i] = false;
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(cardButton[i]->isChecked())
        {
            natureCount[cardList->getNature(card[i])] = true;
        }
    }
    for(int i = 0;i < cardNum;i++)
    {
        if(natureCount[cardList->getNature(card[i])] && !cardButton[i]->isChecked())
        {
            cardButton[i]->setCheckable(false);
        }
        else
        {
            cardButton[i]->setCheckable(true);
        }
    }
    if(sacredCodeCount < characterCount + 2)
    {
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setChecked(false);
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        }
    }
}
void KamishirasawaKeine::sacredCodeCharacterSet()
{
    int characterCount = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            characterCount ++;
        }
    }
    if(!characterCount)
    {
        ensure->setCheckable(false);
    }
    else
    {
        ensure->setCheckable(true);
    }
    if(characterCount == sacredCodeCount - 2)
    {
        for(int i = 0;i < 6;i++)
        {
            if(!paintStruct->gameCharacter[i]->characterPic->isChecked())
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(false);
            }
        }
    }
    else
    {
        for(int i = 0;i < 6;i++)
        {
            paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
        }
    }
}
void KamishirasawaKeine::sendMessageSelf()
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
        case 100://法术反弹响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isChecked())
                {
                    putCharacter(tempMes);
                    putCardCount(tempMes);
                    putCard(tempMes);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://魔道法典响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            putCharacter(tempMes);
            putCardCount(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://圣洁法典响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(3);
            putCharacterCount(tempMes);
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
