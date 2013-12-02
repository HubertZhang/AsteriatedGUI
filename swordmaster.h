#ifndef SWORDMASTER_H
#define SWORDMASTER_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class SwordMaster : public CardAndSkill
{
    Q_OBJECT
public:
    explicit SwordMaster(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    bool ask;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void dialogSet(bool canX[10]);
    void dialogReset();
    void setFrame();
    void selfReset();
    //void skillReset();
signals:

public slots:
    void sendMessageSelf();
};

#endif // SWORDMASTER_H
