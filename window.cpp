#include "window.h"
#include <QPainter>
#include <QString>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
Window::Window(QWidget *parent) :
    QWidget(parent)
{
    paint = false;
    mySource = new MessageSource();
    connect(mySource,SIGNAL(buttonClicked()),this,SLOT(informationGet()));
    phase = 0;
    starBG = new StarBG();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    timer->start(17);
    cardAttack = new CardAttack(this);
    connect(cardAttack,SIGNAL(paintOver()),this,SLOT(changeYPhase()));
    connect(&networkSocket,SIGNAL(readFinished(std::vector<int>)),this,SLOT(messageProcess(std::vector<int>)));
}
void Window::timeOut()
{
    paint = !paint;
    if(paint && phase != 6)
    {
        return;
    }
    repaint();
}
void Window::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);
    switch(phase)
    {
        case 0:
        {
            starBG->paint(event,painter);
            break;
        }
        case 1:
        {
            starBG->paint(event,painter);
            wColor->paint(event,painter);
            break;
        }
        case 2:
        {
            starBG->paint(event,painter);
            wColor->paint(event,painter);
            chooseCharacter->paint(event,painter);
            break;
        }
        case 3:
        {
            starBG->paint(event,painter);
            wColor->paint(event,painter);
            paintStruct->paint(event,painter);
            break;
        }
        case 4:
        {
            starBG->paint(event,painter);
            wColor->paint(event,painter);
            paintStruct->paint(event,painter);
            cardAndSkill->paint(event,painter);
            break;
        }
        case 5:
        {
            starBG->paint(event,painter);
            wColor->paint(event,painter);
            paintStruct->paint(event,painter);
            cardAndSkill->paint(event,painter);
            askDialog->paint(event,painter);
            break;
        }
        case 6:
        {
            starBG->paint(event,painter);
            wColor->paint(event,painter);
            paintStruct->paint(event,painter);
            cardAndSkill->paint(event,painter);
            cardAttack->paint(event,painter);
        }
    }
    delete painter;
}
void Window::messageProcess(std::vector<int> m)
{
    int message[15];
    for(int i = 0; i<15; i++)
    {
        if(i<m.size()) message[i] = m[i];
        else message[i] = 0;
    }
    if(phase == 6)
    {
        cardAttack->destroyPic();
    }
    switch(message[0])
    {
        case 0:
        {
            int color;
            if(message[1] == message[2] || message[1] == message[3] || message[1] == message[4])
            {
                color = 0;
            }
            else
            {
                color = 1;
            }
            int paraColor[6];
            for(int i = 0;i < 5;i++)
            {
                paraColor[i] = (message[1] + 5 - i) % 6;
                if(paraColor[i] == message[2] || paraColor[i] == message[3] || paraColor[i] == message[4])
                {
                    paraColor[i] = 0;
                }
                else
                {
                    paraColor[i] = 1;
                }
            }
            paraColor[5] = color;
            for(int i = 0;i < 15;i++)
            {
                this->paintStructInit[i] = message[i];
            }
            wColor = new PaintColor(paraColor);
            this->phase = 1;
            break;
        }
        case 1:
        {
            chooseCharacter = new ChooseCharacter(message[1],message[2],message[3]);
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->character[0],SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->character[1],SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->character[2],SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->cancel,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->ensure,SLOT(isThisClicked(int,int)));
            connect(chooseCharacter->ensure,SIGNAL(changeClicked()),this,SLOT(changeWPhase()));
            this->phase = 2;
            break;
        }
        case 2:
        {
            int tempOne[15];
            int yourSite = this->paintStructInit[1];
            for(int i = 0;i < 6;i++)
            {
                tempOne[i] = (yourSite + 5 - i) % 6;
            }
            for(int i = 0;i < 6;i++)
            {
                if(tempOne[i] == this->paintStructInit[2] || tempOne[i] == this->paintStructInit[3] || tempOne[i] == this->paintStructInit[4])
                {
                    tempOne[i + 6] = 0;
                }
                else
                {
                    tempOne[i + 6] = 1;
                }
            }
            for(int i = 0;i < 6;i++)
            {
                tempOne[i] = message[tempOne[i] + 1];

            }
            paintStruct = new PaintStruct(tempOne,this);
            for(int i = 0;i < 6;i++)
            {
                connect(this,SIGNAL(mouseClicked(int,int)),paintStruct->gameCharacter[i]->characterPic,SLOT(isThisClicked(int,int)));
            }
            this->phase = 3;
            cardList = new CardList();
            switch(message[paintStructInit[1] + 1])
            {
                case 1:cardAndSkill = new SwordMaster(paintStruct,this);break;
                case 2:cardAndSkill = new Berserker(paintStruct,this);break;
                case 3:cardAndSkill = new ArrowMaid(paintStruct,this);break;
                case 4:cardAndSkill = new SealMaid(paintStruct,this);break;
                case 5:cardAndSkill = new DarkKiller(paintStruct,this);break;
                case 6:cardAndSkill = new PureMaid(paintStruct,this);break;
                default:cardAndSkill = new CardAndSkill(paintStruct,this);break;
            }
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill,SLOT(cardClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill->ensure,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill->cancel,SLOT(isThisClicked(int,int)));
            connect(cardAndSkill->cancel,SIGNAL(changeClicked()),this,SLOT(changeXPhase()));
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill,SLOT(send(int,int)));
            //connect(cardAndSkill,SIGNAL(paintAnime(int[15])),this,SLOT(informationSelf(int[15])));
            break;
        }
        case 3:
        {
            paintStruct->paintArrow = true;
            paintStruct->arrowNum = ((-message[1] + 5 + paintStructInit[1]) % 6);
            break;
        }
        case 4:
        {
            int info[3] = {0,0,0};
            askDialog = new AskDialog(info,this,paintStruct);
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->ensure,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->cancel,SLOT(isThisClicked(int,int)));
            connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            this->phase = 5;
            break;
        }
        case 5:
        {
            int site = ((-message[1] + 5 + paintStructInit[1]) % 6);
            if(message[3])
            {
                paintStruct->gameCharacter[site]->status[paintStruct->gameCharacter[site]->statusNum] = message[2];
                paintStruct->gameCharacter[site]->statusNum ++;
            }
            else
            {
                bool find = false;
                for(int i = 0;i < paintStruct->gameCharacter[site]->statusNum;i++)
                {
                    if(paintStruct->gameCharacter[site]->status[i] == message[2])
                    {
                        find = true;
                    }
                    if(find)
                    {
                        paintStruct->gameCharacter[site]->status[i] = paintStruct->gameCharacter[site]->status[i + 1];
                    }
                }
                paintStruct->gameCharacter[site]->statusNum --;
            }
            break;
        }
        case 6:
        {
            int info[3] = {1,0,0};
            askDialog = new AskDialog(info,this,paintStruct);            
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->ensure,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->cancel,SLOT(isThisClicked(int,int)));
            connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            this->phase = 5;
            break;
        }
        case 7:
        {
            int info[3] = {0,0,0};
            cardAndSkill->linkReset();
            cardAndSkill->changePaintMode(2,info);
            break;
        }
        case 8:
        {
            if(message[1])
            {
                paintStruct->gemBlue += message[2];
                paintStruct->crystalBlue += message[3];
                paintStruct->grailBlue += message[4];
                paintStruct->moraleBlue += message[5];
            }
            else
            {
                paintStruct->gemRed += message[2];
                paintStruct->crystalRed += message[3];
                paintStruct->grailRed += message[4];
                paintStruct->moraleRed += message[5];
            }
            break;
        }
        case 9:
        {
            int site = ((-message[1] + 5 + paintStructInit[1]) % 6);
            paintStruct->gameCharacter[site]->cardNum += message[2];
            paintStruct->gameCharacter[site]->cardLimit += message[3];
            paintStruct->gameCharacter[site]->cure += message[4];
            paintStruct->gameCharacter[site]->gem += message[5];
            paintStruct->gameCharacter[site]->crystal += message[6];
            paintStruct->gameCharacter[site]->yellow += message[7];
            paintStruct->gameCharacter[site]->blue += message[8];
            break;
        }
        case 10:
        {
            //if(information[14] != -1)
            //{
                message[1] = ((-message[1] + 5 + paintStructInit[1]) % 6);
                for(int i = 4;i < 4 + message[2];i ++)
                {
                    message[i] = ((-message[i] + 5 + paintStructInit[1]) % 6);
                }
            //}
            cardAttack->set(message);
            this->phase = 6;
            break;
        }
        case 11:
        {
            int info[3];
            info[0] = message[2];
            info[1] = message[1];
            int site = ((-message[3] + 5 + paintStructInit[1]) % 6);
            info[2] = site;
            cardAndSkill->linkReset();
            cardAndSkill->changePaintMode(1,info);
            break;
        }
        case 12:
        {
            int info[3] = {2,message[1],0};
            askDialog = new AskDialog(info,this,paintStruct);
            connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            this->phase = 5;
            break;
        }
        case 13:
        {
            cardAndSkill->destroyCard();
            for(int i = 0;i < message[1];i++)
            {
                cardAndSkill->card[cardAndSkill->cardNum] = message[2 + i];
                cardAndSkill->cardNum ++;
            }
            cardAndSkill->buttonFixed();
            this->phase = 4;
            break;
        }
        case 14:
        {
            int info[3] = {message[1],message[2],0};
            cardAndSkill->linkReset();
            cardAndSkill->changePaintMode(3,info);
            break;
        }
        case 15:
        {
            cardAndSkill->linkReset();
            cardAndSkill->dialogReset();
            cardAndSkill->setFrame();
            connect(cardAndSkill->ensure,SIGNAL(changeClicked()),cardAndSkill,SLOT(selfReset()));
            bool canX[10];
            for(int i = 0;i < 10;i++)
            {
                canX[i] = false;
            }
            for(int i = 0;i < message[1];i ++)
            {
                canX[message[2 + i]] = true;
            }
            cardAndSkill->dialogSet(canX);
        }
    }
}
void Window::informationGet()
{
    networkSocket.setup((char*)mySource->inputLine->text().toStdString().c_str());
    mySource->close();
//    const char* s = y.c_str();
//    int information[15];
//    for(int i = 0;i < 15;i++)
//    {
//        information[i] = 0;
//    }
//    int i = 0;
//    int j = 0;
//    while(s[i] != '\0')
//    {
//        if(s[i] == '_')
//        {
//            i ++;
//            j ++;
//        }
//        information[j] = information[j]*10 + (s[i] - 48);
//        i ++;
//    }
//    messageProcess(information);
}
/*void Window::informationSelf(int info[])
{
    messageProcess(info);
}*/
void Window::changeWPhase()
{
    phase = 1;
}
void Window::changeXPhase()
{
    phase = 4;
}
void Window::changeYPhase()
{
    phase = 4;
}
void Window::changeZPhase()
{
    delete askDialog;
    phase = 4;
}

void Window::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked(event->x(),event->y());
}
