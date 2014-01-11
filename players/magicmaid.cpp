#include "magicmaid.h"

MagicMaid::MagicMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    //ask = false;
    stormCount = 0;
    //dialog = new NewDialog(windowX);
    //dialog->init(8);//魔弹融合
    magicGroup[0] = new PicButton(80,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(81,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(82,568,559,100,42,false,this);
    /*for(int i = 0;i < dialog->skillCount;i++)
    {
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }*/
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
void MagicMaid::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->setChecked(true);
}
void MagicMaid::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(6);
    magicGroup[1]->setChecked(true);
}
void MagicMaid::magicSetTwo()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(7);
    magicGroup[2]->setChecked(true);
}
void MagicMaid::changeSelfMode(int mode)
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
            if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
    }
    cancel->setCheckable(true);
    switch(mode)
    {
        case 4://魔爆冲击响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                for(int j = 0;j < 6;j ++)
                {
                    if(i != j)
                    {
                        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                    }
                }
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            break;
        }
        /*case 5://魔弹融合响应阶段
        {
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == fire || cardList->getNature(card[i]) == ground)
                {
                    cardButton[i]->setCheckable(true);
                }
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }*/
        case 6://魔弹融合法术响应阶段
        {
            cancel->setCheckable(false);
            int siteCount = 0;
            int left = 0;
            int right = 0;
            int i = 0;
            while(siteCount != 3)
            {
                if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[i]->color)
                {
                    if(siteCount == 0)
                    {
                        left = i;
                    }
                    if(siteCount == 2)
                    {
                        right = i;
                    }
                    siteCount ++;
                }
                i++;
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == fire || cardList->getNature(card[i]) == ground || cardList->getName(card[i]) == missile)
                {
                    cardButton[i]->setCheckable(true);
                }
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
                connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[left]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[left]->characterPic,SLOT(cancelClick()));
                connect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[right]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[right]->characterPic,SLOT(cancelClick()));
            }
            break;
        }
        case 7://毁灭风暴响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
                for(int j = 0;j < 6;j ++)
                {
                    if(i != j)
                    {
                        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
                    }
                }
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
            }
            for(int i = 0;i < 6;i++)
            {
                if(paintStruct->gameCharacter[i]->color != paintStruct->gameCharacter[5]->color)
                {
                    paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                }
            }
            break;
        }
    }
}
//void MagicMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    /*if(ask)
//    {
//        dialog->paint(event,painter);
//    }*/
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
/*void  MagicMaid::setFrame()
{
    ask = true;
}*/
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setChecked(false);
    }
}*/
void MagicMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getType(card[i]) == magic)
        {
            magicGroup[0]->setCheckable(true);
        }
        if(cardList->getNature(card[i]) == ground || cardList->getNature(card[i]) == fire)
        {
            magicGroup[1]->setCheckable(true);
        }
    }
    if(paintStruct->gameCharacter[5]->gem!= 0)
    {
        magicGroup[2]->setCheckable(true);
    }
}
void MagicMaid::skillCancel()
{
    stormCount = 0;
    //ask = false;
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(countPlus()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(countMinus()));
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
}
void MagicMaid::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void MagicMaid::countPlus()
{
    if(stormCount == 0)
    {
        stormCount ++;
        return;
    }
    if(stormCount == 1)
    {
        stormCount ++;
        ensure->setCheckable(true);
        return;
    }
    if(stormCount == 2)
    {
        for(int i = 0;i < 6;i++)
        {
            if(paintStruct->gameCharacter[i]->characterPic->isChecked())
            {
                paintStruct->gameCharacter[i]->characterPic->setChecked(false);
                break;
            }
        }
        return;
    }
}
void MagicMaid::countMinus()
{
    ensure->setCheckable(false);
    stormCount --;
}
/*void MagicMaid::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            changeSelfMode(5 + i);
        }
    }
    dialogReset();
}
void MagicMaid::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void MagicMaid::dialogSet(bool canX[])
{
    dialog->set(canX);
}*/
void MagicMaid::sendMessageSelf()
{
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
    switch(informationKind)
    {
        case 200://魔爆冲击响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            for(int i = 0;i < 6;i++)
            {
                if(paintStruct->gameCharacter[i]->characterPic->isChecked())
                {
                    int site = (-i + paintStruct->yourSite + 5) % 6;
                    tempMes.push_back(site);
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isChecked())
                {
                    tempMes.push_back(card[i]);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
        }
        case 201://魔蛋融合响应阶段
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
        case 202://毁灭风暴响应阶段
        {
            //system("pause");
            tempMes.push_back(1);
            tempMes.push_back(3);
            for(int i = 0;i < 6;i++)
            {
                if(paintStruct->gameCharacter[i]->characterPic->isChecked())
                {
                    int site = (-i + paintStruct->yourSite + 5) % 6;
                    tempMes.push_back(site);
                }
            }
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
