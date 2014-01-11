#ifndef ARROWMAID_H
#define ARROWMAID_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class ArrowMaid : public CardAndSkill
{
    Q_OBJECT
public:
    explicit ArrowMaid(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    PicButton* kiraTrap;
    PicButton* snipe;
    bool ask;
    //void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void dialogSet(bool canX[10]);
    void dialogReset();
    void setFrame();
    void selfReset();
    void skillCancel();
    void sendMessageSelf();
    //void skillReset();
signals:
public slots:
    void kiraTrapRes();
    void snipeRes();
    void skillset();
    void skillClear();
};

#endif // ARROWMAID_H
