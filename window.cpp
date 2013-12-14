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
    chatLine = new QLineEdit(this);
    chatLine->setGeometry(1058,732,302,32);
    QPalette temp = chatLine->palette();
    temp.setBrush(QPalette::Background,QColor(0,0,0,0));
    temp.setBrush(QPalette::Text,QColor(255,255,255,255));
    chatLine->setPalette(QPalette(QColor(0,0,0,0)));
    chatLine->setEnabled(false);
    chatBrowser = new QTextBrowser(this);
    temp = chatBrowser->palette();
    temp.setBrush(QPalette::Base,QColor(0,0,0,0));
    temp.setBrush(QPalette::Text,QColor(255,255,255,255));
    chatBrowser->setPalette(temp);
    chatBrowser->setGeometry(1058,410,302,312);
    connect(&networkSocket,SIGNAL(idReceived(int)),this,SLOT(chatReady(int)));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    timer->start(17);
    cardAttack = new CardAttack(this);
    connect(cardAttack,SIGNAL(paintOver()),this,SLOT(changeYPhase()));
    connect(&networkSocket,SIGNAL(readFinished(std::vector<int>)),this,SLOT(messageProcess(std::vector<int>)));
}
void Window::chatReady(int id)
{
    chatSocket.setup(id,(char*)networkSocket.peerAddress().toString().toStdString().c_str());
    chatLine->setEnabled(true);
    connect(chatLine,SIGNAL(returnPressed()),this,SLOT(sendChatMessage()));
    connect(&chatSocket,SIGNAL(readFinished(int,QString)),this,SLOT(displayMessage(int,QString)));
}

void Window::sendChatMessage()
{
    QString temp = chatLine->text();
    chatLine->clear();
    chatSocket.sendMessage(temp);
}

void Window::displayMessage(int id, QString message)
{
     chatBrowser->append(QString::number(id)+QString(": ")+message);
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
            //system("pause");
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
    int information[15];
    for(int i = 0; i<15; i++)
    {
        if(i<m.size()) information[i] = m[i];
        else information[i] = 0;
    }
    if(phase == 6)
    {
        cardAttack->destroyPic();
    }
    QString s = "";
    for(int i = 0;i < 15;i++)
    {
        s = s + QString::number(information[i]) + " ";
    }
    chatBrowser->append(s);
    switch(information[0])
    {
        case 0:
        {
            int color;
            if(information[1] == information[2] || information[1] == information[3] || information[1] == information[4])
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
                paraColor[i] = (information[1] + 5 - i) % 6;
                if(paraColor[i] == information[2] || paraColor[i] == information[3] || paraColor[i] == information[4])
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
                this->paintStructInit[i] = information[i];
            }
            wColor = new PaintColor(paraColor);
            this->phase = 1;
            break;
        }
        case 1:
        {
            chooseCharacter = new ChooseCharacter(information[1],information[2],information[3]);
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->character[0],SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->character[1],SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->character[2],SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->cancel,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),chooseCharacter->ensure,SLOT(isThisClicked(int,int)));
            connect(chooseCharacter->ensure,SIGNAL(changeClicked()),chooseCharacter,SLOT(sendMessageChoose()));
            connect(chooseCharacter,SIGNAL(sendMessageChooseSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
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
                tempOne[i] = information[tempOne[i] + 1];

            }
            paintStruct = new PaintStruct(tempOne,this,paintStructInit[1]);
            for(int i = 0;i < 6;i++)
            {
                connect(this,SIGNAL(mouseClicked(int,int)),paintStruct->gameCharacter[i]->characterPic,SLOT(isThisClicked(int,int)));
            }
            this->phase = 3;
            cardList = new CardList();
            switch(information[paintStructInit[1] + 1])
            {
                case 1:cardAndSkill = new SwordMaster(paintStruct,this);break;
                case 2:cardAndSkill = new Berserker(paintStruct,this);break;
                case 3:cardAndSkill = new ArrowMaid(paintStruct,this);break;
                case 4:cardAndSkill = new SealMaid(paintStruct,this);break;
                case 5:cardAndSkill = new DarkKiller(paintStruct,this);break;
                case 6:cardAndSkill = new PureMaid(paintStruct,this);break;
                case 7:cardAndSkill = new Angel(paintStruct,this,this);break;
                case 8:cardAndSkill = new MagicMaid(paintStruct,this);break;
                case 9:cardAndSkill = new MagicSword(paintStruct,this);break;
                case 10:cardAndSkill = new PureSpear(paintStruct,this,this);break;
                case 11:cardAndSkill = new ElementMaster(paintStruct,this);break;
                case 12:cardAndSkill = new Adventurer(paintStruct,this,this);break;
                case 13:cardAndSkill = new Necromancer(paintStruct,this,this);break;
                case 14:cardAndSkill = new ArbitrationMaid(paintStruct,this);break;
                case 15:cardAndSkill = new PriestMaid(paintStruct,this,this);break;
                case 16:cardAndSkill = new PrayMaid(paintStruct,this);break;
                default:cardAndSkill = new CardAndSkill(paintStruct,this);break;
            }
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill,SLOT(cardClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill->ensure,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill->cancel,SLOT(isThisClicked(int,int)));
            connect(cardAndSkill,SIGNAL(sendMessageDisSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(cardAndSkill,SIGNAL(sendMessageInSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(cardAndSkill,SIGNAL(sendMessageSelfSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(cardAndSkill,SIGNAL(sendMessageIceSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(cardAndSkill,SIGNAL(sendMessageMisSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(cardAndSkill,SIGNAL(sendMessageOneSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(cardAndSkill->cancel,SIGNAL(changeClicked()),this,SLOT(changeXPhase()));
            connect(this,SIGNAL(mouseClicked(int,int)),cardAndSkill,SLOT(send(int,int)));
            //connect(cardAndSkill,SIGNAL(paintAnime(int[15])),this,SLOT(informationSelf(int[15])));
            break;
        }
        case 3:
        {
            paintStruct->paintArrow = true;
            paintStruct->arrowNum = ((-information[1] + 5 + paintStructInit[1]) % 6);
            break;
        }
        case 4:
        {
            int info[3] = {0,0,0};
            askDialog = new AskDialog(info,this,paintStruct);
            askDialog->informationKind = 4;
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->ensure,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->cancel,SLOT(isThisClicked(int,int)));
            connect(askDialog,SIGNAL(sendMessageWeakSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            this->phase = 5;
            break;
        }
        case 5:
        {
            int site = ((-information[1] + 5 + paintStructInit[1]) % 6);
            if(information[3])
            {
                paintStruct->gameCharacter[site]->status[paintStruct->gameCharacter[site]->statusNum] = information[2];
                paintStruct->gameCharacter[site]->statusNum ++;
            }
            else
            {
                bool find = false;
                for(int i = 0;i < paintStruct->gameCharacter[site]->statusNum;i++)
                {
                    if(paintStruct->gameCharacter[site]->status[i] == information[2])
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
            askDialog->informationKind = 6;
            //cardAndSkill->linkReset();
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->ensure,SLOT(isThisClicked(int,int)));
            connect(this,SIGNAL(mouseClicked(int,int)),askDialog->cancel,SLOT(isThisClicked(int,int)));
            connect(askDialog,SIGNAL(sendMessageSpeSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            this->phase = 5;
            break;
        }
        case 7:
        {
            int info[3] = {0,0,0};
            cardAndSkill->informationKind = 7;
            cardAndSkill->linkReset();
            cardAndSkill->changePaintMode(2,info);
            break;
        }
        case 8:
        {
            if(information[1])
            {
                paintStruct->gemBlue = information[2];
                paintStruct->crystalBlue = information[3];
                paintStruct->grailBlue = information[4];
                paintStruct->moraleBlue = information[5];
            }
            else
            {
                paintStruct->gemRed = information[2];
                paintStruct->crystalRed = information[3];
                paintStruct->grailRed = information[4];
                paintStruct->moraleRed = information[5];
            }
            break;
        }
        case 9:
        {
            int site = ((-information[1] + 5 + paintStructInit[1]) % 6);
            paintStruct->gameCharacter[site]->cardNum += information[2];
            paintStruct->gameCharacter[site]->cardLimit += information[3];
            paintStruct->gameCharacter[site]->cure += information[4];
            paintStruct->gameCharacter[site]->gem += information[5];
            paintStruct->gameCharacter[site]->crystal += information[6];
            paintStruct->gameCharacter[site]->yellow += information[7];
            paintStruct->gameCharacter[site]->blue += information[8];
            break;
        }
        case 10:
        {
            //if(information[14] != -1)
            //{
                information[1] = ((-information[1] + 5 + paintStructInit[1]) % 6);
                for(int i = 4;i < 4 + information[2];i ++)
                {
                    information[i] = ((-information[i] + 5 + paintStructInit[1]) % 6);
                }
            //}
            cardAttack->set(information);
            this->phase = 6;
            break;
        }
        case 11:
        {
            int info[3];
            info[0] = information[2];
            info[1] = information[1];
            int site = ((-information[3] + 5 + paintStructInit[1]) % 6);
            info[2] = site;
            cardAndSkill->informationKind = 11;
            cardAndSkill->linkReset();
            cardAndSkill->changePaintMode(1,info);
            break;
        }
        case 12:
        {
            int info[3] = {2,information[1],0};
            askDialog = new AskDialog(info,this,paintStruct);
            askDialog->informationKind = 12;
            connect(askDialog,SIGNAL(sendMessageCureSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
            connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
            this->phase = 5;
            break;
        }
        case 13:
        {
            cardAndSkill->destroyCard();
            for(int i = 0;i < information[1];i++)
            {
                cardAndSkill->card[cardAndSkill->cardNum] = information[2 + i];
                cardAndSkill->cardNum ++;
            }
            cardAndSkill->buttonFixed();
            this->phase = 4;
            break;
        }
        case 14://SHOULE BE ADD
        {
            int info[3] = {information[1],information[2],0};
            cardAndSkill->linkReset();
            cardAndSkill->changePaintMode(3,info);
            cardAndSkill->informationKind = 14;
            break;
        }
        case 15:
        {
            cardAndSkill->linkReset();
            cardAndSkill->dialogReset();
            cardAndSkill->setFrame();
            cardAndSkill->setResPara(information[2 + information[1]]);
            connect(cardAndSkill->ensure,SIGNAL(changeClicked()),cardAndSkill,SLOT(selfReset()));
            bool canX[10];
            for(int i = 0;i < 10;i++)
            {
                canX[i] = false;
            }
            for(int i = 0;i < information[1];i ++)
            {
                canX[information[2 + i]] = true;
            }
            cardAndSkill->dialogSet(canX);
            cardAndSkill->cancel->canBeClicked = true;
            cardAndSkill->informationKind = 39;//THANK YOU.
            break;
        }
        case 16:
        {
            int site = ((-information[1] + 5 + paintStructInit[1]) % 6);
            paintStruct->gameCharacter[site]->activated = information[2];
            break;
        }
        case 17://弃牌函数
        {
            cardAndSkill->informationKind = 17;
            cardAndSkill->linkReset();
            cardAndSkill->dialogReset();
            cardAndSkill->discard(information[1]);
            break;
        }
        case 18://特殊对话框
        {
            switch(information[1])
            {
                case 4:
                {
                    int info[3] = {0,0,0};
                    askDialog = new AskDialog(info,this,paintStruct);
                    askDialog->labelOne->setText("威力赐福");
                    askDialog->labelTwo->setText("");
                    askDialog->informationKind = 4;
                    connect(this,SIGNAL(mouseClicked(int,int)),askDialog->ensure,SLOT(isThisClicked(int,int)));
                    connect(this,SIGNAL(mouseClicked(int,int)),askDialog->cancel,SLOT(isThisClicked(int,int)));
                    connect(askDialog,SIGNAL(sendMessageWeakSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
                    connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
                    connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
                    this->phase = 5;
                    break;
                }
                case 5:
                {
                    int info[3] = {0,0,0};
                    askDialog = new AskDialog(info,this,paintStruct);
                    askDialog->labelOne->setText("迅捷赐福");
                    askDialog->labelTwo->setText("");
                    askDialog->informationKind = 4;
                    connect(this,SIGNAL(mouseClicked(int,int)),askDialog->ensure,SLOT(isThisClicked(int,int)));
                    connect(this,SIGNAL(mouseClicked(int,int)),askDialog->cancel,SLOT(isThisClicked(int,int)));
                    connect(askDialog,SIGNAL(sendMessageWeakSig(std::vector<int>)),this,SLOT(sendMessageWindow(std::vector<int>)));
                    connect(askDialog->ensure,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
                    connect(askDialog->cancel,SIGNAL(changeClicked()),this,SLOT(changeZPhase()));
                    this->phase = 5;
                    break;
                }
            }
            break;
        }
        case 19://增加一次行动
        {
            cardAndSkill->linkReset();
            cardAndSkill->dialogReset();
            cardAndSkill->append(information[1]);
            break;
        }
        case 20://魔蛋响应
        {
            cardAndSkill->linkReset();
            cardAndSkill->dialogReset();
            cardAndSkill->missileAttack();
            break;
        }
        case 21://圣女的冰霜祷言
        {
            cardAndSkill->linkReset();
            cardAndSkill->dialogReset();
            cardAndSkill->icePoetry();
            cardAndSkill->informationKind = 21;
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
    delete chooseCharacter;
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
    if(paintStruct->gameCharacter[5]->characterNum == 15 && askDialog->kind[0] == 1)
    {
        if(askDialog->activateGroup[0]->isClicked)
        {
            cardAndSkill->priestAct();
        }
    }
    for(int i = 0;i < 6;i++)
    {
        paintStruct->gameCharacter[i]->characterPic->isClicked = false;
        paintStruct->gameCharacter[i]->characterPic->canBeClicked = false;
    }
    if(paintStruct->gameCharacter[5]->characterNum == 12)
    {
        for(int i = 0;i < 6;i++)
        {
            disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),askDialog,SLOT(adventureRefine()));
            for(int j = 0;j < 6;j++)
            {
                disconnect(paintStruct->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStruct->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
    }
    delete askDialog;
    phase = 4;
}
void Window::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked(event->x(),event->y());
}
void Window::sendMessageWindow(std::vector<int> messageSend)
{
    int information[15];
    for(int i = 0; i<15; i++)
    {
        if(i < messageSend.size()) information[i] = messageSend[i];
        else information[i] = 0;
    }
    QString s = "";
    for(int i = 0;i < 15;i++)
    {
        s = s + QString::number(information[i]) + " ";
    }
    chatBrowser->append(s);
    chatBrowser->append(QString::number(-100));
    networkSocket.sendMessage(messageSend);
}
