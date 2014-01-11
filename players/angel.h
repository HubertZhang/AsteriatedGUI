#ifndef ANGEL_H
#define ANGEL_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"
class Window;
class Angel : public CardAndSkill
{
    Q_OBJECT
public:
    explicit Angel(PaintStruct* paintStruct,QWidget *parent,Window* windowAngel);
    NewDialog* dialog;
    NewDialog* windClear;
    NumberDialog* kamiPro;
    PicButton* magicGroup[3];
    bool reminiscence;
    bool ask;
    bool proAsk;
    int blessCount;
    int morale;
    //void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void skillCancel();
    void selfReset();
    void setResPara(int);
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void skillset();
    void skillClear();
    void countPlus();
    void countMinus();
    void reminiscenceSet();
    void reminiscenceReset();
};

#endif // ANGEL_H
