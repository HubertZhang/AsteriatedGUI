#ifndef MAGICSWORD_H
#define MAGICSWORD_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class MagicSword : public CardAndSkill
{
    Q_OBJECT
public:
    explicit MagicSword(PaintStruct* paintStruct,QWidget *parent);
    PicButton* darkMeteor;
    NewDialog* dialog;
    int magicCount;
    bool ask;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void magicSwordSet();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void skillset();
    void skillClear();
    void countPlus();
    void countMinus();
};
#endif // MAGICSWORD_H
