#include "choosecharacter.h"

ChooseCharacter::ChooseCharacter(int numOne,int numTwo,int numThree,QWidget *parent) :
    QWidget(parent)
{
    bg = new QPixmap();
    bg->load(":/character/chooseCharacterFrame");
    character[0] = new PicButton(numOne,356,270,147,207,true);
    character[1] = new PicButton(numTwo,515,270,147,207,true);
    character[2] = new PicButton(numThree,674,270,147,207,true);
    ensure = new PicButton(32,595,479,100,42,false);
    cancel = new PicButton(33,715,480,100,42,false);
    connect(cancel,SIGNAL(notClicked()),character[0],SLOT(cancelX()));
    connect(cancel,SIGNAL(notClicked()),character[1],SLOT(cancelX()));
    connect(cancel,SIGNAL(notClicked()),character[2],SLOT(cancelX()));
    connect(cancel,SIGNAL(notClicked()),ensure,SLOT(cancelX()));
    connect(cancel,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
    for(int i = 0;i < 3;i++)
    {
        connect(character[i],SIGNAL(changeClicked()),character[(i + 1) % 3],SLOT(cancelX()));
        connect(character[i],SIGNAL(changeClicked()),character[(i + 2) % 3],SLOT(cancelX()));
        connect(character[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(character[i],SIGNAL(changeClicked()),cancel,SLOT(recoverClick()));
        connect(character[i],SIGNAL(notClicked()),ensure,SLOT(cancelX()));
        connect(character[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(character[i],SIGNAL(notClicked()),cancel,SLOT(cancelX()));
        connect(character[i],SIGNAL(notClicked()),cancel,SLOT(cancelClick()));
    }
}
void ChooseCharacter::paint(QPaintEvent *event, QPainter *painter)
{
    painter->drawPixmap(328,247,bg->width(),bg->height(),*bg);
    character[0]->paint(event,painter);
    character[1]->paint(event,painter);
    character[2]->paint(event,painter);
    ensure->paint(event,painter);
    cancel->paint(event,painter);
}

