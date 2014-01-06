#ifndef BERSERKER_H
#define BERSERKER_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class Berserker : public CardAndSkill
{
    Q_OBJECT
public:
    explicit Berserker(PaintStruct* paintStruct,QWidget *parent);
    NewDialog* dialog;
    bool ask;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void dialogSet(bool canX[10]);
    void dialogReset();
    void setFrame();
    void selfReset();
    void sendMessageSelf();
    //void skillReset();
signals:

public slots:

};

#endif // BERSERKER_H
