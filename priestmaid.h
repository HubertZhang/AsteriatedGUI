#ifndef PRIESTMAID_H
#define PRIESTMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"
class Window;
class PriestMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit PriestMaid(PaintStruct* paintStruct,QWidget *parent,Window* deathX);
    PicButton* magicGroup[4];
    bool ask;
    NewDialog* dialog;
    AskDialog* sacredContract;
    bool sacredContractPaint;
    int magicCount;
    int cureCount;
    int sacredZoneCount;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void priestAct();
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void magicSetThree();
    void skillset();
    void skillClear();
    void magicPlus();
    void magicMinus();
    void zonePlus();
    void zoneMinus();
    void waterPhase();
    void contractSet();
    void contractReset();
    void curePlus();
    void cureMinus();
};

#endif // PRIESTMAID_H
