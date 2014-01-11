#include "sealmaid.h"

SealMaid::SealMaid(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    dialog = new NewDialog(windowX);
    sealBreak = new NewDialog(windowX);
    dialog->init(4);//法术激荡
    sealBreak->init(101);
    reminiscence = false;
    for(int i = 0;i < 1;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
    }
    for(int i = 0;i < 10;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),sealBreak->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    //system("pause");
    magicGroup[0] = new PicButton(66,362,559,100,42,false,this);
    magicGroup[1] = new PicButton(67,465,559,100,42,false,this);
    magicGroup[2] = new PicButton(68,568,559,100,42,false,this);
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
    for(int i = 0;i < 10;i++)
    {
        connect(sealBreak->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(sealBreak->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < 10;j++)
        {
            if(i != j)
            {
                connect(sealBreak->skillGroup[i],SIGNAL(changeClicked()),sealBreak->skillGroup[j],SLOT(cancelX()));
            }
        }
    }
    //system("pause");
}
void SealMaid::magicSetZero()
{
    linkReset();
    skillset();
    sealBreak->label->hide();
    changeSelfMode(5);
    magicGroup[0]->setChecked(true);
}
void SealMaid::magicSetOne()
{

    linkReset();
    skillset();
    sealBreak->label->hide();
    //system("pause");
    changeSelfMode(6);
    magicGroup[1]->setChecked(true);
}
void SealMaid::magicSetTwo()
{
    linkReset();
    skillset();
    sealBreak->label->hide();
    changeSelfMode(7);
    reminiscenceReset();
    magicGroup[2]->setChecked(true);
}
void SealMaid::changeSelfMode(int mode)
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
        case 4://法术激荡响应阶段
        {
            //system("pause");
            //system("pause");
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == attack)
                {
                    cardButton[i]->setCheckable(true);
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 5://五系封印响应阶段
        {
            cancel->setCheckable(false);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getSkillOne(card[i])/10 == 4)
                {
                    cardButton[i]->setCheckable(true);
                }
                for(int j = 0;j < 6;j++)
                {
                    if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                    {
                        for(int k = 0;k < paintStruct->gameCharacter[j]->statusNum;k++)
                        {
                            if(cardList->getSkillOne(paintStruct->gameCharacter[j]->status[k]) == cardList->getSkillOne(card[i]))
                            {
                                disconnect(cardButton[i],SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                                disconnect(cardButton[i],SIGNAL(notClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                            }
                        }
                    }
                }
            }
            break;
        }
        case 6://五系束缚响应阶段
        {
            cancel->setCheckable(false);
            for(int j = 0;j < 6;j++)
            {
                if(paintStruct->gameCharacter[5]->color != paintStruct->gameCharacter[j]->color)
                {
                    paintStruct->gameCharacter[j]->characterPic->setCheckable(true);
                }
            }
            break;
        }
        case 7://封印破碎
        {
            reminiscence = true;
            cancel->setCheckable(false);
            for(int i = 0;i < 6;i++)
            {
                paintStruct->gameCharacter[i]->characterPic->setCheckable(true);
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(reminiscenceReset()));
                connect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(reminiscenceSet()));
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            }
            break;
        }
    }
}
//void SealMaid::paint(QPaintEvent *event, QPainter *painter)
//{
//    if(ask)
//    {
//        dialog->paint(event,painter);
//        cancel->setCheckable(true);
//    }
//    if(reminiscence)
//    {
//        sealBreak->paint(event,painter);
//        //cancel->setCheckable(true);
//    }
//    ensure->paint(event,painter);
//    cancel->paint(event,painter);
//    for(int i = 0;i < 3;i++)
//    {
//        magicGroup[i]->paint(event,painter);
//    }
//    for(int i = 0;i < cardNum;i++)
//    {
//        cardButton[i]->paint(event,painter);
//    }
//}
void SealMaid::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void SealMaid::setFrame()
{
    ask = true;
}
void SealMaid::selfReset()
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
void SealMaid::dialogReset()
{
    //system("pause");
    dialog->label->hide();
    sealBreak->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->setCheckable(false);
        dialog->skillGroup[i]->setChecked(false);
    }
}
void SealMaid::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getSkillOne(card[i])/10 == 4)
        {
            //system("pause");
            magicGroup[0]->setCheckable(true);
        }
    }
    //system("pause");
    if(paintStruct->gameCharacter[5]->gem + paintStruct->gameCharacter[5]->crystal != 0)
    {
        magicGroup[1]->setCheckable(true);
        magicGroup[2]->setCheckable(true);
    }
    //system("pause");
}
void SealMaid::skillCancel()
{
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->setCheckable(false);
        magicGroup[i]->setChecked(false);
    }
    sealBreak->label->hide();
    reminiscence = false;
    for(int i = 0;i < 6;i++)
    {
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),this,SLOT(reminiscenceSet()));
        disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(notClicked()),this,SLOT(reminiscenceReset()));
    }
    for(int i = 0;i < 10;i++)
    {
        sealBreak->skillGroup[i]->setCheckable(false);
        sealBreak->skillGroup[i]->setChecked(false);
    }
    //system("pause");
}
void SealMaid::skillClear()
{
    int info[3] = {0,0,0};
    reminiscence = false;
    sealBreak->label->hide();
    linkReset();
    changePaintMode(2,info);
}
void SealMaid::reminiscenceSet()
{
    reminiscenceReset();
    int point = 0;
    for(int i = 0;i < 6;i++)
    {
        if(paintStruct->gameCharacter[i]->characterPic->isChecked())
        {
            point = i;
            break;
        }
    }
    for(int i = 0;i < paintStruct->gameCharacter[point]->statusNum;i++)
    {
        if(cardList->getType(paintStruct->gameCharacter[point]->status[i]) == magic)
        {
            switch(cardList->getName(paintStruct->gameCharacter[point]->status[i]))
            {
                case poison:sealBreak->skillGroup[0]->setCheckable(true);break;
                case weak:sealBreak->skillGroup[1]->setCheckable(true);break;
                case shield:sealBreak->skillGroup[2]->setCheckable(true);break;
            }
        }
        else
        {
            if(cardList->getSkillOne(paintStruct->gameCharacter[point]->status[i])/10 == 4)
            {
                sealBreak->skillGroup[cardList->getSkillOne(card[i]) % 10 + 2]->setCheckable(true);
            }
            else
            {
                sealBreak->skillGroup[cardList->getSkillOne(card[i]) % 10 + 7]->setCheckable(true);
            }
        }
    }
}
void SealMaid::reminiscenceReset()
{
    for(int i = 0;i < 10;i++)
    {
        sealBreak->skillGroup[i]->setCheckable(false);
    }
    ensure->setCheckable(false);
}
void SealMaid::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isChecked())
        {
            informationKind = 100 + i;
        }
    }
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
        case 100://法术激荡响应阶段
        {
            tempMes.push_back(1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://元素封印响应阶段
        {
        //system("pause");
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
        case 201://五系束缚响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(3);
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
        case 202://封印破碎响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(4);
            for(int i = 0;i < 10;i++)
            {
                if(sealBreak->skillGroup[i]->isChecked())
                {
                    int cardAttribute = getCardName(i);
                    for(int j = 0;j < 6;j++)
                    {
                        if(paintStruct->gameCharacter[j]->characterPic->isChecked())
                        {
                            int site = (-j + paintStruct->yourSite + 5) % 6;
                            tempMes.push_back(site);
                            for(int k = 0;k < paintStruct->gameCharacter[j]->statusNum;k++)
                            {
                                if(cardList->getName(paintStruct->gameCharacter[j]->status[k]) == cardAttribute || cardList->getSkillOne(paintStruct->gameCharacter[j]->status[k]) == cardAttribute)
                                {
                                    tempMes.push_back(paintStruct->gameCharacter[j]->status[k]);
                                    emit sendMessageSelfSig(tempMes);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
        default:
        {
            sendMessageIn();
        }
    }
}
int SealMaid::getCardName(int i)
{
    switch(i)
    {
        case 0:return poison;
        case 1:return weak;
        case 2:return shield;
        case 3:return 41;
        case 4:return 42;
        case 5:return 43;
        case 6:return 44;
        case 7:return 45;
        case 8:return 161;
        case 9:return 162;
    }
}
