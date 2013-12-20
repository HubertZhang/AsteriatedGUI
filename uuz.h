#ifndef UUZ_H
#define UUZ_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"
class Window;
class UUZ : public CardAndSkill
{
    Q_OBJECT
public:
    explicit UUZ(PaintStruct* paintStruct,QWidget *parent,Window* soulX);
    PicButton* magicGroup[4];
    NewDialog* dialog;
    AskDialog* soulLink;
    bool ask;
    bool soulAsk;
    int soulCount;
    int linkDamage;
    int mirrorCount;
    int mirrorLine;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    void damageSet(int);
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void magicSetThree();
    void skillset();
    void skillClear();
    void soulPlus();
    void soulMinus();
    void mirrorPlus();
    void mirrorMinus();
};

#endif // UUZ_H
