#ifndef PRAYMAID_H
#define PRAYMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"

class PrayMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit PrayMaid(PaintStruct* paintStruct,QWidget *parent);
    PicButton* magicGroup[4];
    bool ask;
    NewDialog* dialog;
    int lightCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void magicSetThree();
    void skillset();
    void skillClear();
    void lightPlus();
    void lightMinus();
};

#endif // PRAYMAID_H
