#include "cardbutton.h"
#include <QString>
#include <QTextCodec>
#include <string>

CardButton::CardButton(int card,int paraX,int paraY, QWidget *parent)
    :PicButton(paraX,paraY,GEO_CARD_W,GEO_CARD_H,true,parent)
{
    //isConnect = false;
    frameLabel.setPixmap(QPixmap(":/character/cardFrameX.png"));
    QString s;
    for(int i = 0;i < 5;i ++)
    {
        label[i] = new QLabel(this);
    }
    QString qnature[] = {QString::fromLocal8Bit("地"),QString::fromLocal8Bit("水"),QString::fromLocal8Bit("火"),QString::fromLocal8Bit("风"),QString::fromLocal8Bit("雷"),QString::fromLocal8Bit("暗"),QString::fromLocal8Bit("光")};
    QString qname[] = {QString::fromLocal8Bit("地斩"),QString::fromLocal8Bit("水斩"),QString::fromLocal8Bit("火斩"),QString::fromLocal8Bit("风斩"),QString::fromLocal8Bit("雷斩"),QString::fromLocal8Bit("暗斩"),QString::fromLocal8Bit("中毒"),QString::fromLocal8Bit("虚弱"),QString::fromLocal8Bit("魔弹"),QString::fromLocal8Bit("圣盾"),QString::fromLocal8Bit("圣光")};
    QString qkind[] = {QString::fromLocal8Bit("技"),QString::fromLocal8Bit("血"),QString::fromLocal8Bit("圣"),QString::fromLocal8Bit("幻"),QString::fromLocal8Bit("咏")};
    label[0]->setText(qnature[cardlist.getNature(card)]);
    label[1]->setText(qname[cardlist.getName(card)]);
    label[2]->setText(qkind[cardlist.getKind(card)]);
    s.sprintf("%d",cardlist.getSkillOne(card));
    label[3]->setText(s);
    s.sprintf("%d",cardlist.getSkillTwo(card));
    label[4]->setText(s);
    //TODO
//    int yOffset = 20;
//    for(int i = 0;i < 5;i ++)
//    {
//        label[i]->move(xp + 20,yp + yOffset * (i + 1));
//        label[i]->show();
//    }
}
