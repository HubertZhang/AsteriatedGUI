#ifndef SWORDKING_H
#define SWORDKING_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
#include "askdialog.h"
class Window;
class SwordKing : public CardAndSkill
{
    Q_OBJECT
public:
    explicit SwordKing(PaintStruct* paintStruct,QWidget *parent,Window* swordX);
    NewDialog* dialog;
    bool ask;
    bool swordAsk;
    int lastAttack;
    AskDialog* swordCut;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    void lastAttackSet(int);
    //void skillReset();
signals:
public slots:
    void attackSet();
    void attackReset();
};


#endif // SWORDKING_H
