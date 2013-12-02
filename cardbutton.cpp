#include "cardbutton.h"
#include <QString>
#include <string>
QString qnature[] = {"地","水","火","风","雷","暗","光"};
QString qname[] = {"地斩","水斩","火斩","风斩","雷斩","暗斩","中毒","虚弱","魔弹","圣盾","圣光"};
QString qkind[] = {"技","血","圣","幻","咏"};
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
    //s.sprintf("%d",cardList->getNature(cardNum));
    label[0]->setText(qnature[cardList->getNature(cardNum)]);
    //s.sprintf("%d",cardList->getName(cardNum));
    label[1]->setText(qname[cardList->getName(cardNum)]);
    //s.sprintf("%d",cardList->getKind(cardNum));
    label[2]->setText(qkind[cardList->getKind(cardNum)]);
    s.sprintf("%d",cardList->getSkillOne(cardNum));
    label[3]->setText(s);
    s.sprintf("%d",cardList->getSkillTwo(cardNum));
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
