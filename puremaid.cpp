#include "puremaid.h"
#include <QString>
PureMaid::PureMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    pureLightCount = 0;
    pureCureCount = 0;
    pureCureFrame = new FrameLabel(windowX);
    //dialog->init(6);//无响应
    magicGroup[0] = new PicButton(71,362,559,100,42,false);
    magicGroup[1] = new PicButton(72,465,559,100,42,false);
    magicGroup[2] = new PicButton(74,568,559,100,42,false);
    for(int i = 0;i < 3;i++)
    {
        select[i] = 0;
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
    pureCureFrame->labelOne->setText(QString::fromUtf8("你妹啊让不让用中文了"));
    pureCureFrame->labelTwo->setText("");
    frame = false;
}
void PureMaid::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void PureMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
}
void PureMaid::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(7);
    magicGroup[2]->isClicked = true;
}
void PureMaid::changeSelfMode(int mode)
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
            if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
    }
    cancel->canBeClicked = true;
    switch(mode)
    {
        case 4://治疗术响应阶段
        {
            cancel->canBeClicked = false;
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i]) == 61)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                    connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
               }
            }
            //disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 5://治愈之光响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                for(int j = 0;j < 6;j ++)
                {
                    if(i != j)
                    {
                        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
                    }
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i]) == 62)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                    connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                }
            }
            break;
        }
        case 7://圣疗响应阶段
        {
        //  system("pause");
            cancel->canBeClicked = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
            }
            connect(ensure,SIGNAL(changeClicked()),this,SLOT(pureCurePlus()));
            //system("pause");
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
            frame = true;
            //system("pause");
            break;
        }
        case 8://冰霜祷言响应阶段
        {
            cancel->canBeClicked  = false;
            for(int i = 0;i < 6;i++)
            {
                paintStructX->gameCharacter[i]->characterPic->canBeClicked = true;
            }
            break;
        }
    }
}
void PureMaid::paint(QPaintEvent *event, QPainter *painter)
{
    if(frame)
    {
        pureCureFrame->paint(event,painter);
    }
    for(int i = 0;i < 3;i++)
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
void PureMaid::setFrame()
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
void PureMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillOne(card[i]) == 61)
        {
            magicGroup[0]->canBeClicked = true;
        }
        if(cardList->getSkillOne(card[i]) == 62)
        {
            magicGroup[1]->canBeClicked = true;
        }
    }
    if(paintStructX->gameCharacter[5]->gem + paintStructX->gameCharacter[5]->crystal != 0)
    {
        magicGroup[2]->canBeClicked = true;
    }
}
void PureMaid::skillCancel()
{
    pureLightCount = 0;
    frame = false;
    pureCureCount = 0;
    //pureCureFrame->reset();
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
        disconnect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
    for(int i = 0;i < 6;i++)
    {
        disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(pureCurePlus()));
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
}
void PureMaid::skillClear()
{
    int info[3] = {0,0,0};
    pureCureFrame->labelOne->hide();
    linkReset();
    changePaintMode(2,info);
}
void PureMaid::countPlus()
{
    ensure->canBeClicked = true;
    if(pureLightCount < 3)
    {
        pureLightCount ++;
    }
    else
    {
        for(int i = 0;i < 6;i++)
        {
            if(paintStructX->gameCharacter[i]->characterPic->isClicked)
            {
                paintStructX->gameCharacter[i]->characterPic->isClicked = false;
                break;
            }
        }
    }
}
void PureMaid::countMinus()
{
    pureLightCount --;
    if(pureLightCount == 0)
    {
        ensure->canBeClicked = false;
    }
}
void PureMaid::pureCurePlus()
{
    pureCureCount ++;
    ensure->isClicked = false;
    ensure->canBeClicked = false;
    for(int i = 0;i < 6;i++)
    {
        if(paintStructX->gameCharacter[i]->characterPic->isClicked)
        {
            int site = (-i + paintStructX->yourSite + 5) % 6;
            select[pureCureCount - 1] = site;
        }
    }
    for(int i = 0;i < 6;i++)
    {
        paintStructX->gameCharacter[i]->characterPic->isClicked = false;
    }
    if(pureCureCount == 3)
    {
        sendMessageCardAndSkill();
        //system("pause");
        linkReset();
        pureCureFrame->reset();
        disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
    }
}
void PureMaid::icePoetry()
{
    informationKind = 200;
    changeSelfMode(8);
}
void PureMaid::sendMessageSelf()
{
    for(int i = 0;i < 3;i++)
    {
        if(magicGroup[i]->isClicked)
        {
            informationKind = 201 + i;
        }
    }
    std::vector<int> tempMes;
    if(cancel->isClicked && informationKind < 100)
    {
        tempMes.push_back(0);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    switch(informationKind)
    {
        case 200://冰霜祷言响应阶段
        {
            for(int j = 0;j < 6;j++)
            {
                if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                {
                    int site = (-j + paintStructX->yourSite + 5) % 6;
                    tempMes.push_back(site);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
        }
        case 201://治疗术响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    for(int j = 0;j < 6;j++)
                    {
                        if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                        {
                            int site = (-j + paintStructX->yourSite + 5) % 6;
                            tempMes.push_back(site);
                            tempMes.push_back(card[i]);
                            emit sendMessageSelfSig(tempMes);
                            return;
                        }
                    }
                }
            }
        }
        case 202://治愈之光响应阶段
        {
            //system("pause");
            tempMes.push_back(1);
            tempMes.push_back(3);
            int messageCount = 0;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    tempMes.push_back(card[i]);
                }
            }
            for(int j = 0;j < 6;j++)
            {
                if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                {
                    messageCount ++;
                }
            }
            tempMes.push_back(messageCount);
            tempMes.push_back(select[0]);
            tempMes.push_back(select[1]);
            tempMes.push_back(select[2]);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 203://圣疗响应阶段
        {
            if(pureCureCount == 3)
            {
                tempMes.push_back(1);
                tempMes.push_back(4);
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                    {
                        int site = (-j + paintStructX->yourSite + 5) % 6;
                        tempMes.push_back(site);
                    }
                }
                emit sendMessageSelfSig(tempMes);
                return;
            }
        }
        default:
        {
            sendMessageIn();
        }
    }
}
