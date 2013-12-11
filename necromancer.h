#ifndef NECROMANCER_H
#define NECROMANCER_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"
class Window;
class Necromancer : public CardAndSkill
{
    Q_OBJECT
public:
    explicit Necromancer(PaintStruct* paintStruct,QWidget *parent,Window* deathX);
    PicButton* magicGroup[3];
    NewDialog* dialog;
    AskDialog* deathTouch;
    bool ask;
    bool deathPaint;
    int deathCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
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
    void deathSet();
    void deathReset();
};

#endif // NECROMANCER_H
