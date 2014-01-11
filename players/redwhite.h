#ifndef REDWHITE_H
#define REDWHITE_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "askdialog.h"
class Window;
class RedWhite : public CardAndSkill
{
    Q_OBJECT
public:
    explicit RedWhite(PaintStruct* paintStruct,QWidget *parent,Window* bloodX);
    NumberDialog* blood;
    PicButton* magicGroup[4];
    bool bloodAsk;
    bool lifeLink;
    int bloodCount;
    int curseCount;
    int curseLine;
    int lifeLinkCha;
    //void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void skillCancel();
    void sendMessageSelf();
    bool redWhiteLink();
    void lifeLinkOver();
    void clickRedWhiteSet();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void magicSetThree();
    void skillset();
    void skillClear();
    void bloodPlus();
    void bloodMinus();
    void cursePlus();
    void curseMinus();
    void bloodSet();
};


#endif // REDWHITE_H
