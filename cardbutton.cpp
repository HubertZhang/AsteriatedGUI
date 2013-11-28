#include "cardbutton.h"
#include <QString>
CardButton::CardButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canBe,int cardNum, QWidget *parent)
    :PicButton(buttonKind,paraX,paraY,paraW,paraH,canBe)
{
    cardList = new CardList();
    isConnect = false;
    QString s;
    for(int i = 0;i < 5;i ++)
    {
        label[i] = new QLabel(parent);
    }
    s.sprintf("%d",cardList->getNature(cardNum));
    label[0]->setText(s);
    s.sprintf("%d",cardList->getName(cardNum));
    label[1]->setText(s);
    s.sprintf("%d",cardList->getKind(cardNum));
    label[2]->setText(s);
    s.sprintf("%d",cardList->getSkillOne(cardNum));
    label[3]->setText(s);
    s.sprintf("%d",cardList->getSkillTwo(cardNum));
    label[4]->setText(s);
    int yOffset = 20;
    for(int i = 0;i < 5;i ++)
    {
        label[i]->move(xp + 20,yp + yOffset * (i + 1));
        label[i]->show();
    }
}
CardButton::~CardButton()
{
    for(int i = 0;i < 5;i++)
    {
        delete label[i];
    }
}
