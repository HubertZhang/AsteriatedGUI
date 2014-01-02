#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <QWidget>
#include "cardandskill.h"
#include "picbutton.h"
#include "newdialog.h"
class window;
class Butterfly : public CardAndSkill
{
    Q_OBJECT
public:
    explicit Butterfly(PaintStruct* paintStruct,QWidget *parent);
    PicButton* magicGroup[3];
    PicButton* tokenPic;
    int confuseCount;
    int deadflyCount;
    int cryCount;
    bool ask;
    bool tokenPaint;
    NewDialog* dialog;
    CardButton* tokenButton[8];
    int token[8];
    int tokenNum;
    void paint(QPaintEvent *, QPainter *);
    void changeSelfMode(int mode);
    void setFrame();
    void skillCancel();
    void dialogSet(bool canX[10]);
    void dialogReset();
    void selfReset();
    void sendMessageSelf();
    void storeStatus();
    void reStore();
    bool storeArray[100];
    void butterflyTokenAdd(int tokenX[6]);
    //void skillReset();
signals:
public slots:
    void magicSetZero();
    void magicSetOne();
    void magicSetTwo();
    void skillset();
    void skillClear();
    void tokenSet();
    void tokenReset();
    void confusePlus();
    void confuseMinus();
    void deadflyPlus();
    void deadflyMinus();
    void tokenClicked(int,int);
};

#endif // BUTTERFLY_H
