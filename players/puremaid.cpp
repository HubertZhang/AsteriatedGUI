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
    magicGroup[0] = new PicButton(71,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(72,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(74,568,559,100,42,false,this);
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
                connect(magicGroup[i],SIGNAL(beChecked()),magicGroup[j],SLOT(setCheckedFalse()));
            }
        }
    }
    //system("pause");
    connect(magicGroup[0],SIGNAL(beChecked()),this,SLOT(magicSetZero()));
    connect(magicGroup[1],SIGNAL(beChecked()),this,SLOT(magicSetOne()));
    connect(magicGroup[2],SIGNAL(beChecked()),this,SLOT(magicSetTwo()));
    for(int i = 0;i < 3;i++)
    {
        connect(magicGroup[i],SIGNAL(unChecked()),this,SLOT(skillClear()));
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
    magicGroup[0]->setChecked(true);
}
void PureMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->setChecked(true);
}
void PureMaid::magicSetTwo()
{
    linkReset();
    skillset();
    changeSelfMode(7);
    magicGroup[2]->setChecked(true);;
}
void PureMaid::changeSelfMode(int mode)
{
    for(int i = 0;i < cardNum;i++)
    {
        for(int j = 0;j < cardNum;j++)
        {
            if(i != j)
            {
                connect(cardButton[i],SIGNAL(beChecked()),cardButton[j],SLOT(setCheckedFalse()));
            }
        }
        for(int j = 0;j < 6;j++)
        {
            if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
            }
        }
    }
    cancel->setCheckable(true);
    switch(mode)
    {
        case 4://治疗术响应阶段
        {
            cancel->setCheckable(false);
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i]) == 61)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
               }
            }
            //disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
        case 5://治愈之光响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
                for(int j = 0;j < 6;j ++)
                {
                    if(i != j)
                    {
                        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckedFalse()));
                    }
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i]) == 62)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            for(int i = 0;i < 6;i++)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(countPlus()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(countMinus()));
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                        disconnect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                    }
                    connect(cardButton[i],SIGNAL(beChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableTrue()));
                    connect(cardButton[i],SIGNAL(unChecked()),paintStruct->gameCharacter[j]->characterPic,SLOT(setCheckableFalse()));
                }
            }
            break;
        }
        case 7://圣疗响应阶段
        {
            //system("pause");
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            }
            connect(ensure,SIGNAL(beChecked()),this,SLOT(pureCurePlus()));
            //system("pause");
            disconnect(ensure,SIGNAL(beChecked()),this,SLOT(reset()));
            frame = true;
            //system("pause");
            break;
        }
        case 8://冰霜祷言响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
            }
            break;
        }
    }
}
//void PureMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(frame)
//    {
//        pureCureFrame->paint(event,painter);
//    }
//    for(int i = 0;i < 3;i++)
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
void PureMaid::setFrame()
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
void PureMaid::skillset()
{
    //system("pause");
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillOne(card[i]) == 61)
        {
            magicGroup[0]->setCheckable(true);
        }
        if(cardList->getSkillOne(card[i]) == 62)
        {
            magicGroup[1]->setCheckable(true);
        }
    }
    if(paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal != 0)
    {
        magicGroup[2]->setCheckable(true);
    }
}
void PureMaid::skillCancel()
{
    //system("pause");
    pureLightCount = 0;
    frame = false;
    pureCureCount = 0;
    //pureCureFrame->reset();
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(beChecked()),this,SLOT(countPlus()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(unChecked()),this,SLOT(countMinus()));
    }
    for(int i = 0;i < 6;i++)
    {
        disconnect(ensure,SIGNAL(beChecked()),this,SLOT(pureCurePlus()));
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
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
    ensure->setCheckable(true);
    if(pureLightCount < 3)
    {
        pureLightCount ++;
    }
    else
    {
        for(int i = 0;i < 6;i++)
        {
            if(paintStruct->gameCharacter[i]->characterPic->isChecked())
            {
                paintStruct->gameCharacter[i]->characterPic->setChecked(false);
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
        ensure->setCheckable(false);
    }
}
void PureMaid::pureCurePlus()
{
    pureCureCount ++;
    ensure->setChecked(false);
    ensure->setCheckable(false);
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            int site = (-i + paintStruct->yourSite + 5) % 6;
            select[pureCureCount - 1] = site;
        }
    }
    for(int i = 0;i < 6;i++)
    {
        paintStruct->gameCharacter[i]->characterPic->setChecked(false);
    }
    if(pureCureCount == 3)
    {
        sendMessageCardAndSkill();
        pureCureFrame->labelOne->hide();
        pureCureFrame->labelTwo->hide();
        //system("pause");
        linkReset();
        connect(ensure,SIGNAL(beChecked()),this,SLOT(reset()));
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
        if(magicGroup[i]->isChecked())
        {
            informationKind = 201 + i;
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
    switch(informationKind)
    {
        case 200://冰霜祷言响应阶段
        {
            for(int j = 0;j < 6;j++)
            {
                if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                {
                    int site = (-j + paintStruct->yourSite + 5) % 6;
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
                if(cardButton[i]->isChecked())
                {
                    for(int j = 0;j < 6;j++)
                    {
                        if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                        {
                            int site = (-j + paintStruct->yourSite + 5) % 6;
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
                if(cardButton[i]->isChecked())
                {
                    tempMes.push_back(card[i]);
                }
            }
            for(int j = 0;j < 6;j++)
            {
                if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                {
                    messageCount ++;
                }
            }
            tempMes.push_back(messageCount);
            for(int j = 0;j < 6;j++)
            {
                if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                {
                    int site = (-j + paintStruct->yourSite + 5) % 6;
                    tempMes.push_back(site);
                }
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 203://圣疗响应阶段
        {
            if(pureCureCount == 3)
            {
                tempMes.push_back(1);
                tempMes.push_back(4);
                tempMes.push_back(select[0]);
                tempMes.push_back(select[1]);
                tempMes.push_back(select[2]);
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
