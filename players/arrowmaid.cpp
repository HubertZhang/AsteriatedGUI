#include "arrowmaid.h"

ArrowMaid::ArrowMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(3);//贯穿射击,精准射击
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 2;j++)
        {
            if(i != j)
            {
                connect(dialog->skillGroup[i],SIGNAL(beChecked()),dialog->skillGroup[j],SLOT(setCheckedFalse()));
            }
        }
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
        connect(dialog->skillGroup[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
        connect(dialog->skillGroup[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
    }
    kiraTrap = new PicButton(62,362,559,100,42,false,this);
    snipe = new PicButton(64,465,559,100,42,false,this);
    connect(this,SIGNAL(mouseClick(int,int)),kiraTrap,SLOT(isThisClicked(int,int)));
    connect(this,SIGNAL(mouseClick(int,int)),snipe,SLOT(isThisClicked(int,int)));
    connect(kiraTrap,SIGNAL(beChecked()),snipe,SLOT(setCheckedFalse()));
    connect(snipe,SIGNAL(beChecked()),kiraTrap,SLOT(setCheckedFalse()));
    connect(kiraTrap,SIGNAL(beChecked()),this,SLOT(kiraTrapRes()));
    connect(snipe,SIGNAL(beChecked()),this,SLOT(snipeRes()));
    connect(kiraTrap,SIGNAL(unChecked()),this,SLOT(skillClear()));
    connect(snipe,SIGNAL(unChecked()),this,SLOT(skillClear()));
}
void ArrowMaid::changeSelfMode(int mode)
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
        case 6://闪光陷阱响应阶段
        {
            cancel->setCheckable(false);
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillTwo(card[i]) == 31)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            //disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
        case 4://贯穿射击响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->setCheckable(true);
                    connect(cardButton[i],SIGNAL(beChecked()),ensure,SLOT(setCheckableTrue()));
                    connect(cardButton[i],SIGNAL(unChecked()),ensure,SLOT(setCheckableFalse()));
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
                }
            }
            break;
        }
        case 5://精准射击响应阶段
        {
            emit resetSignal();
            disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            break;
        }
        case 7://狙击
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                //disconnect(ensure,SIGNAL(beChecked()),this,SLOT(selfReset()));
            }
            break;
        }
    }
}
//void ArrowMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//        cancel->setCheckable(true);
//    }
//    kiraTrap->paint(event,painter);
//    snipe->paint(event,painter);
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    for(int i = 0;i < cardNum;i++)
//    {
//        cardButton[i]->paint(event,painter);
//    }
//}
void ArrowMaid::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void ArrowMaid::setFrame()
{
    ask = true;
}
void ArrowMaid::selfReset()
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
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setChecked(false);
    }
}*/
void ArrowMaid::dialogReset()
{
    //system("pause");
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void ArrowMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillTwo(card[i]) == 31)
        {
            kiraTrap->setCheckable(true);
        }
    }
    if(paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal != 0)
    {
        snipe->setCheckable(true);
    }
}
void ArrowMaid::skillCancel()
{
    snipe->setCheckable(false);
    kiraTrap->setCheckable(false);
    snipe->setChecked(false);
    kiraTrap->setChecked(false);
}
void ArrowMaid::kiraTrapRes()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    kiraTrap->setChecked(true);
}
void ArrowMaid::snipeRes()
{
    linkReset();
    skillset();
    changeSelfMode(7);
    snipe->setChecked(true);
}
void ArrowMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void ArrowMaid::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            informationKind = 100 + i;
        }
    }
    if(kiraTrap->isChecked())
    {
        informationKind = 200;
    }
    if(snipe->isChecked())
    {
        informationKind = 201;
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
        case 100://贯穿射击响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isChecked())
                {
                    tempMes.push_back(card[i]);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(informationKind - 100 + 1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://闪光陷阱响应阶段
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
        case 101://精准射击响应阶段
        {
            tempMes.push_back(3);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 201://狙击响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
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
        default:
        {
            sendMessageIn();
        }
    }
}
