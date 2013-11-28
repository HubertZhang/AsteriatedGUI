#include "askdialog.h"
#include "window.h"
#include <cstdlib>
#include <iostream>
using namespace std;
AskDialog::AskDialog(int information[3],Window *parent,PaintStruct* paintStruct)
{
    storeData = paintStruct;
    storeWindow = parent;
    bg = new QPixmap();
    bg->load(":/character/chooseCharacterFrame.png");
    ensure = new PicButton(32,595,479,100,42,false);
    cancel = new PicButton(33,715,479,100,42,true);
    connect(ensure,SIGNAL(changeClicked()),this,SLOT(destroyLabel()));
    connect(cancel,SIGNAL(changeClicked()),this,SLOT(destroyLabel()));
    labelOne = new QLabel(parent);
    labelTwo = new QLabel(parent);
    for(int i = 0;i < 3;i ++)
    {
        kind[i] = information[i];
    }
    font = new QFont();
    font->setPointSize(30);
    font->setBold(true);
    palette = new QPalette();
    palette->setColor(QPalette::WindowText,Qt::yellow);
    if(kind[0] == 1)
    {
        ensure->canBeClicked = false;
        int offsetX = 0;
        int offsetY = 12 + 42;
        actNum = getActivatedNum(storeData->gameCharacter[5]->characterNum);
        bool activateTwo[2];
        activeInit(storeData->gameCharacter[5]->characterNum);
        //system("pause");
        for(int i = 0;i < 2;i++)
        {
            activateTwo[i] = false;
        }
        bool activateAllow = false;
        if(actNum == 1)
        {
            activateTwo[0] = canActivate(1);
            activateAllow = canActivate(1);
            //system("pause");
            activateGroup[0]->canBeClicked = activateTwo[0];
        }
        //system("pause");
        if(actNum == 2)
        {
            activateTwo[0] = canActivate(1);
            activateTwo[1] = canActivate(2);
            activateAllow = activateTwo[0] || activateTwo[1];
            activateGroup[0]->canBeClicked = activateTwo[0];
            activateGroup[1]->canBeClicked = activateTwo[1];
        }
        //system("pause");
        attributeGroup[0] = new PicButton(34,9 + 328 + offsetX,257,100,42,activateAllow);
        bool refineAllow = false;
        int color = storeData->gameCharacter[5]->color;
        int stone = 0;
        if(color)
        {
            stone = storeData->crystalBlue + storeData->gemBlue;
        }
        else
        {
            stone = storeData->crystalRed + storeData->gemRed;
        }
        if(stone && (storeData->gameCharacter[5]->gem + storeData->gameCharacter[5]->crystal != storeData->gameCharacter[5]->energeLimit))
        {
            refineAllow = true;
        }
        attributeGroup[1] = new PicButton(35,9 + 328 + offsetX,257 + offsetY,100,42,refineAllow);
        int crystalExist = 0;
        int gemExist = 0;
        if(color)
        {
            crystalExist = storeData->crystalBlue;
            gemExist = storeData->gemBlue;
        }
        else
        {
            crystalExist = storeData->crystalRed;
            gemExist = storeData->gemRed;
        }
        bool refine[5];
        for(int i = 0;i < 5;i++)
        {
            refine[i] = false;
        }
        if(!crystalExist && !gemExist)
        {
        }
        if(!crystalExist && gemExist == 1)
        {
            refine[0] = true;
        }
        if(!gemExist && crystalExist == 1)
        {
            refine[1] = true;
        }
        if(!crystalExist && gemExist == 2)
        {
            refine[0] = true;
            refine[2] = true;
        }
        if(!gemExist && crystalExist == 2)
        {
            refine[1] = true;
            refine[4] = true;
        }
        if(gemExist == 1 && crystalExist == 1)
        {
            refine[0] = true;
            refine[1] = true;
            refine[2] = true;
        }
        if(gemExist == 2 && crystalExist == 1)
        {
            refine[0] = true;
            refine[1] = true;
            refine[2] = true;
            refine[3] = true;
        }
        if(gemExist == 1 && crystalExist == 2)
        {
            refine[0] = true;
            refine[1] = true;
            refine[3] = true;
            refine[4] = true;
        }
        if(gemExist > 1 && crystalExist > 1)
        {
            for(int i = 0;i < 5;i++)
            {
                refine[i] = true;
            }
        }
        stone = storeData->gameCharacter[5]->crystal + storeData->gameCharacter[5]->gem;
        if(storeData->gameCharacter[5]->energeLimit == stone)
        {
            for(int i = 0;i < 5;i++)
            {
                refine[i] = false;
            }
        }
        if(storeData->gameCharacter[5]->energeLimit == stone + 1)
        {
            for(int i = 2;i < 5;i++)
            {
                refine[i] = false;
            }
        }
        refineGroup[0] = new PicButton(38,9 + 328 + 100 + offsetX * 2,257 + offsetY,50,42,refine[0]);
        refineGroup[1] = new PicButton(39,9 + 328 + 100 + 50 + offsetX * 3,257 + offsetY,50,42,refine[1]);
        refineGroup[2] = new PicButton(40,9 + 328 + 100 + 50 * 2 + offsetX * 4,257 + offsetY,100,42,refine[2]);
        refineGroup[3] = new PicButton(41,9 + 328 + 100 * 2 + 50 * 2 + offsetX * 5,257 + offsetY,100,42,refine[3]);
        refineGroup[4] = new PicButton(42,9 + 328 + 100 * 3 + 50 * 2 + offsetX * 6,257 + offsetY,100,42,refine[4]);
        bool buyAllow = false;
        if(storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum > 2)
        {
            buyAllow = true;
        }
        bool buy[3];
        for(int i = 0;i < 3;i++)
        {
            buy[i] = false;
        }
        if(color)
        {
            stone = storeData->gemBlue + storeData->crystalBlue;
        }
        else
        {
            stone = storeData->gemRed + storeData->crystalRed;
        }
        attributeGroup[2] = new PicButton(36,9 + 328 + offsetX,257 + offsetY * 2,100,42,buyAllow);
        if(stone == 5)
        {
            connect(attributeGroup[2],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            connect(attributeGroup[2],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        }
        if(stone == 4)
        {
            buy[0] = true;
            buy[1] = true;
        }
        if(stone < 4)
        {
            buy[2] = true;
        }
        if(storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum < 3)
        {
            for(int i = 0;i < 3;i++)
            {
                buyGroup[i] = false;
            }
        }
        buyGroup[0] = new PicButton(43,9 + 328 + 100 + offsetX * 2,257 + offsetY * 2,50,42,buy[0]);
        buyGroup[1] = new PicButton(44,9 + 328 + 100 + 50 + offsetX * 3,257 + offsetY * 2,50,42,buy[1]);
        buyGroup[2] = new PicButton(41,9 + 328 + 100 + 50 * 2 + offsetX * 4,257 + offsetY * 2,100,42,buy[2]);
        bool composeAllow = false;
        if(color)
        {
            if((storeData->crystalBlue + storeData->gemBlue > 2) && (storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum > 2))
            {
                composeAllow = true;
            }
        }
        else
        {
            if((storeData->crystalRed + storeData->gemRed > 2) && (storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum > 2))
            {
                composeAllow = true;
            }
        }
        bool compose[3];
        for(int i = 0;i < 3;i++)
        {
            compose[i] = false;
        }
        if(color)
        {
            stone = storeData->gemBlue;
        }
        else
        {
            stone = storeData->gemRed;
        }
        if(stone > 3)
        {
            stone = 3;
        }
        for(int i = 0;i < stone;i++)
        {
            compose[i] = true;
        }
        if(storeData->gameCharacter[5]->cardLimit - storeData->gameCharacter[5]->cardNum < 3)
        {
            for(int i = 0;i < 3;i++)
            {
                compose[i] = false;
            }
        }
        if(color)
        {
            stone = storeData->gemBlue + storeData->crystalBlue;
        }
        else
        {
            stone = storeData->gemRed + storeData->crystalRed;
        }
        if(stone < 3)
        {
            for(int i = 0;i < 3;i++)
            {
                compose[i] = false;
            }
        }
        attributeGroup[3] = new PicButton(37,9 + 328 + offsetX,257 + offsetY * 3,100,42,composeAllow);
        if(stone > 2)
        {
            if(color)
            {
                stone = storeData->gemBlue;
            }
            else
            {
                stone = storeData->gemRed;
            }
            if(stone == 0)
            {
                connect(attributeGroup[3],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(attributeGroup[3],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            }
        }
        composeGroup[0] = new PicButton(43,9 + 328 + 100 + offsetX * 2,257 + offsetY * 3,50,42,compose[0]);
        composeGroup[1] = new PicButton(46,9 + 328 + 100 + 50 + offsetX * 3,257 + offsetY * 3,100,42,compose[1]);
        composeGroup[2] = new PicButton(47,9 + 328 + 100 * 2 + 50 + offsetX * 4,257 +offsetY * 3,100,42,compose[2]);
        for(int i = 0;i < actNum;i ++)
        {
            connect(activateGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            connect(storeWindow,SIGNAL(mouseClicked(int,int)),activateGroup[i],SLOT(isThisClicked(int,int)));
        }
        for(int i = 0;i < 5;i++)
        {
            connect(refineGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            connect(storeWindow,SIGNAL(mouseClicked(int,int)),refineGroup[i],SLOT(isThisClicked(int,int)));
        }
        for(int i = 0;i < 3;i++)
        {
            connect(buyGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            connect(storeWindow,SIGNAL(mouseClicked(int,int)),buyGroup[i],SLOT(isThisClicked(int,int)));
        }
        for(int i = 0;i < 3;i++)
        {
            connect(composeGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
            connect(storeWindow,SIGNAL(mouseClicked(int,int)),composeGroup[i],SLOT(isThisClicked(int,int)));
        }
        for(int i = 0;i < 4;i++)
        {
            connect(attributeGroup[i],SIGNAL(changeClicked()),ensure,SLOT(cancelClick()));
        }
        for(int i = 0; i < 4;i++)
        {
            connect(storeWindow,SIGNAL(mouseClicked(int,int)),attributeGroup[i],SLOT(isThisClicked(int,int)));
            for(int j = 0;j < 4;j++)
            {
                if(i != j)
                {
                    connect(attributeGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
                }
                for(int k = 0;k < actNum;k++)
                {
                    if(i != 0)
                    {
                        connect(attributeGroup[i],SIGNAL(changeClicked()),activateGroup[k],SLOT(cancelX()));
                    }
                }
                for(int k = 0;k < 5;k ++)
                {
                    if(i != 1)
                    {
                        connect(attributeGroup[i],SIGNAL(changeClicked()),refineGroup[k],SLOT(cancelX()));
                    }
                }
                for(int k = 0;k < 3;k++)
                {
                    if(i != 2)
                    {
                        connect(attributeGroup[i],SIGNAL(changeClicked()),buyGroup[k],SLOT(cancelX()));
                    }
                }
                for(int k = 0;k < 3;k++)
                {
                    if(i != 3)
                    {
                        connect(attributeGroup[i],SIGNAL(changeClicked()),composeGroup[k],SLOT(cancelX()));
                    }
                }
            }
            connect(attributeGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        }
        for(int i = 0;i < actNum;i++)
        {
            connect(activateGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 4;j++)
            {
                if(j == 0)
                {
                    connect(activateGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
                }
                else
                {
                    connect(activateGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
                }
            }
            for(int j = 0;j < actNum;j++)
            {
                if(i != j)
                {
                    connect(activateGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
                }
            }
            for(int j = 0;j < 5;j++)
            {
                connect(activateGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
            }
            for(int j = 0;j < 3;j++)
            {
                connect(activateGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
                connect(activateGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
            }
        }
        for(int i = 0;i < 5;i++)
        {
            connect(refineGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 4;j++)
            {
                if(j == 1)
                {
                    connect(refineGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
                }
                else
                {
                    connect(refineGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
                }
            }
            for(int j = 0;j < 5;j++)
            {
                if(i != j)
                {
                    connect(refineGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
                }
            }
            for(int j = 0;j < 3;j++)
            {
                connect(refineGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
                connect(refineGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
            }
            for(int j = 0;j < actNum;j++)
            {
                connect(refineGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
            }
        }
        for(int i = 0;i < 3;i++)
        {
            connect(buyGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 4;j++)
            {
                if(j == 2)
                {
                    connect(buyGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
                }
                else
                {
                    connect(buyGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
                }
            }
            for(int j = 0;j < 5;j++)
            {
                connect(buyGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
            }
            for(int j = 0;j < 3;j++)
            {
                if(i != j)
                {
                    connect(buyGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
                }
                connect(buyGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
            }
            for(int j = 0;j < actNum;j++)
            {
                connect(buyGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
            }
        }
        for(int i = 0;i < 3;i++)
        {
            connect(composeGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            for(int j = 0;j < 4;j++)
            {
                if(j == 3)
                {
                    connect(composeGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(recover()));
                }
                else
                {
                    connect(composeGroup[i],SIGNAL(changeClicked()),attributeGroup[j],SLOT(cancelX()));
                }
            }
            for(int j = 0;j < 5;j++)
            {
                connect(composeGroup[i],SIGNAL(changeClicked()),refineGroup[j],SLOT(cancelX()));
            }
            for(int j = 0;j < 3;j++)
            {
                if(i != j)
                {
                    connect(composeGroup[i],SIGNAL(changeClicked()),composeGroup[j],SLOT(cancelX()));
                }
                connect(composeGroup[i],SIGNAL(changeClicked()),buyGroup[j],SLOT(cancelX()));
            }
            for(int j = 0;j < actNum;j++)
            {
                connect(composeGroup[i],SIGNAL(changeClicked()),activateGroup[j],SLOT(cancelX()));
            }
        }
    }
    if(kind[0] == 2)
    {
        connect(storeWindow,SIGNAL(mouseClicked(int,int)),ensure,SLOT(isThisClicked(int,int)));
        connect(storeWindow,SIGNAL(mouseClicked(int,int)),cancel,SLOT(isThisClicked(int,int)));
        for(int i = 0;i < 5;i++)
        {
            if(i < storeData->gameCharacter[5]->cure && i < information[1])
            {
                number[i] = new PicButton(i + 49,99 + 328 + 70 * i,407,50,50,true);
                connect(storeWindow,SIGNAL(mouseClicked(int,int)),number[i],SLOT(isThisClicked(int,int)));
                connect(number[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(number[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            }
            else
            {
                number[i] = new PicButton(i + 49,99 + 328 + 70 * i,407,50,50,false);
            }
        }
        for(int i = 0;i < 5;i++)
        {
            for(int j = 0;j < 5;j++)
            {
                if(i != j)
                {
                    connect(number[i],SIGNAL(changeClicked()),number[j],SLOT(cancelX()));
                }
            }
        }
    }
    //font->setPointSize();
}
AskDialog::~AskDialog()
{
    delete ensure;
    delete cancel;
    if(kind[0] == 1)
    {
        for(int i = 0;i < 5;i++)
        {
            delete refineGroup[i];
        }
        for(int i = 0;i < 3;i++)
        {
            delete buyGroup[i];
            delete composeGroup[i];
        }
        for(int i = 0;i < actNum;i++)
        {
            delete activateGroup[i];
        }
    }
    if(kind[0] == 2)
    {
        for(int i = 0;i < 5;i++)
        {
            delete number[i];
        }
    }
}

void AskDialog::paint(QPaintEvent* event, QPainter* painter)
{
    painter->drawPixmap(328,247,bg->width(),bg->height(),*bg);
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    switch(kind[0])
    {
        case 0:
        {
            ensure->canBeClicked = true;
            QString* s = new QString(QString::fromUtf8("询问虚弱: 确定跳过回合,"));
            labelOne->setText(*s);
            labelOne->setFont(*font);
            labelOne->setPalette(*palette);
            labelOne->move(328 + 25,247 + 20);
            labelOne->show();
            s = new QString(QString::fromUtf8("取消接三张牌."));
            labelTwo->setText(*s);
            labelTwo->setFont(*font);
            labelTwo->setPalette(*palette);
            labelTwo->move(328 + 25,247 + 60);
            labelTwo->show();
            delete s;
            break;
        }
        case 1:
        {
            for(int i = 0;i < actNum;i++)
            {
                activateGroup[i]->paint(event,painter);
            }
            for(int i = 0;i < 4;i++)
            {
                attributeGroup[i]->paint(event,painter);
            }
            for(int i = 0;i < 5;i++)
            {
                refineGroup[i]->paint(event,painter);
            }
            for(int i = 0;i < 3;i++)
            {
                buyGroup[i]->paint(event,painter);
            }
            for(int i = 0;i < 3;i++)
            {
                composeGroup[i]->paint(event,painter);
            }
            break;
        }
        case 2:
        {
            QString* s;
            //s = new QString(QString::fromUtf8("取消接三张牌."));
            s = new QString(QString::fromUtf8("请选择治疗,伤害:"));
            labelOne->setText(*s);
            labelOne->setFont(*font);
            labelOne->setPalette(*palette);
            labelOne->move(328 + 25,247 + 20);
            labelOne->show();
            s->sprintf("%d",kind[1]);
            labelTwo->setText(*s);
            labelTwo->setFont(*font);
            labelTwo->setPalette(*palette);
            labelTwo->move(328 + 25,247 + 60);
            labelTwo->show();
            for(int i = 0;i < 5;i++)
            {
                number[i]->paint(event,painter);
            }
            break;
        }
    }
}
void AskDialog::destroyLabel()
{
    delete labelOne;
    delete labelTwo;
}
int AskDialog::getActivatedNum(int characterNum)
{
    switch(characterNum)
    {
        case 5:
        case 6:
        case 9:
        case 15:
        case 16:
        {
            return 1;
            break;
        }
        case 14:
        case 20:
        case 22:
        case 23:
        {
            return 2;
            break;
        }
        default:
        {
            return 0;
            break;
        }
    }
}
void AskDialog::activeInit(int characterNum)
{
    switch(characterNum)
    {
        case 5:
        {
            activateGroup[0] = new PicButton(70,9 + 328 + 100,257,100,42,false);
            //system("pause");
            break;
        }
        case 6:
        {
            activateGroup[0] = new PicButton(73,9 + 328 + 100,257,100,42,false);
            break;
        }
        case 9:
        case 15:
        case 16:
        {
            break;
        }
        case 14:
        case 20:
        case 22:
        case 23:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

bool AskDialog::canActivate(int skill)
{
    int skillNum = storeData->gameCharacter[5]->characterNum * 10 + skill;
    switch(skillNum)
    {
        case 51:
        {
            if(storeData->gameCharacter[5]->gem != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 61:
        {
            if(storeData->gameCharacter[5]->gem != 0 && !storeData->gameCharacter[5]->isActivated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 91:
        {
            return true;
            break;
        }
        case 151:
        {
            if((storeData->gameCharacter[5]->crystal != 0 || storeData->gameCharacter[5]->gem != 0) && storeData->gameCharacter[5]->cure != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 161:
        {
            if(storeData->gameCharacter[5]->gem != 0 && !storeData->gameCharacter[5]->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 141:
        {
            if(storeData->gameCharacter[5]->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 142:
        {
            if(storeData->gameCharacter[5]->gem != 0 && !storeData->gameCharacter[5]->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 201:
        {
            if(storeData->gameCharacter[5]->yellow > 2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 202:
        {
            if(storeData->gameCharacter[5]->gem != 0 || storeData->gameCharacter[5]->crystal != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 221:
        {
            if(storeData->gameCharacter[5]->yellow > 0 && storeData->gameCharacter[5]->blue > 0 && !storeData->gameCharacter[5]->activated)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        case 222:
        {
            if(storeData->gameCharacter[5]->gem != 0)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        default:
        {
            return true;
            break;
        }
    }
}
