#ifndef PURESPEAR_H
#define PURESPEAR_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"
class Window;
class PureSpear : public CardAndSkill
{
    Q_OBJECT
public:
    explicit PureSpear(PaintStruct* paintStruct,QWidget *parent,Window* groundX);
    PicButton* magicGroup[3];
    NewDialog* dialog;
    AskDialog* groundSpear;
    bool ask;
    bool spearAsk;
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
    void skillset();
    void skillClear();
};
#endif // PURESPEAR_H
