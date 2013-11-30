#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "askdialog.h"
class Window;
class Adventurer : public CardAndSkill
{
    Q_OBJECT
public:
    explicit Adventurer(PaintStruct* paintStruct,QWidget *parent,Window* advenX);
    PicButton* magicGroup[3];
    int cheatCount;
    AskDialog* cheat;
    bool cheatPaint;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void skillCancel();
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
    void cheatSet();
    void cheatReset();
};

#endif // ADVENTURER_H
