#include "cardbutton.h"
#include <QString>
#include <QTextCodec>
#include <string>

CardButton::CardButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canBe,int cardNum, QWidget *parent)
    :PicButton(buttonKind,paraX,paraY,paraW,paraH,canBe,parent)
{
    cardList = new CardList();
    isConnect = false;
    QString s;
    for(int i = 0;i < 5;i ++)
    {
        label[i] = new QLabel(parent);
    }
    //  QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QString qnature[] = {QString::fromLocal8Bit("地"),QString::fromLocal8Bit("水"),QString::fromLocal8Bit("火"),QString::fromLocal8Bit("风"),QString::fromLocal8Bit("雷"),QString::fromLocal8Bit("暗"),QString::fromLocal8Bit("光")};
    QString qname[] = {QString::fromLocal8Bit("地斩"),QString::fromLocal8Bit("水斩"),QString::fromLocal8Bit("火斩"),QString::fromLocal8Bit("风斩"),QString::fromLocal8Bit("雷斩"),QString::fromLocal8Bit("暗斩"),QString::fromLocal8Bit("中毒"),QString::fromLocal8Bit("虚弱"),QString::fromLocal8Bit("魔弹"),QString::fromLocal8Bit("圣盾"),QString::fromLocal8Bit("圣光")};
    QString qkind[] = {QString::fromLocal8Bit("技"),QString::fromLocal8Bit("血"),QString::fromLocal8Bit("圣"),QString::fromLocal8Bit("幻"),QString::fromLocal8Bit("咏")};
    //s.sprintf("%d",cardList->getNature(cardNum));
    label[0]->setText(qnature[cardList->getNature(cardNum)]);
    //s.sprintf("%d",cardList->getName(cardNum));
    label[1]->setText(qname[cardList->getName(cardNum)]);
    //s.sprintf("%d",cardList->getKind(cardNum));
    label[2]->setText(qkind[cardList->getKind(cardNum)]);
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
