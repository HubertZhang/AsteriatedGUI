#ifndef ASKDIALOG_H
#define ASKDIALOG_H

#include <QButtonGroup>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QPalette>
//#include "picbutton.h"
#include "paintstruct.h"
//class Window;
class AskDialog : public QLabel
{
    Q_OBJECT
public:
    //Window* storeWindow;
    //QString s;
    //QPixmap* bg;
    QButtonGroup operate;
    PicButton* ensure;
    PicButton* cancel;
    QFont font;
    QLabel* labelOne;
    QLabel* labelTwo;
    QPalette palette;
    PaintStruct* paintStruct;
//    PicButton* attributeGroup[4];
//    PicButton* activateGroup[2];
//    PicButton* refineGroup[5];
//    PicButton* buyGroup[4];
//    PicButton* composeGroup[4];
//    PicButton* number[5];
//    int actNum;
//    bool redWhite;
//    int informationKind;
//    int getActivatedNum(int characterNum);
//    void activeInit(int characterNum);
//    void paint(QPaintEvent*,QPainter*);
//    bool canActivate(int skillNum);
    explicit AskDialog(PaintStruct*,QWidget* parent);
    //~AskDialog();
    int kind[3];
signals:
    void activateSig(bool,bool);
    void sendMessageSpeSig(std::vector<int>);
    void sendMessageWeakSig(std::vector<int>);
    void sendMessageCureSig(std::vector<int>);
public slots:
    //void destroyLabel();
    
    virtual void ensureClicked();
    virtual void cancelClicked();
    //void sendMessageSpe();
    //void sendMessageWeak();
    //void sendMessageCure();
    //void sendMessageAskDialog();

};

class WeakDialog : public AskDialog
{
    Q_OBJECT
    
    QLabel text;
public:
    WeakDialog(PaintStruct*,QWidget* parent);
public slots:
    void ensureClicked();
    void cancelClicked();
};

class ActiveDialog : public AskDialog
{
    Q_OBJECT
    
    QButtonGroup choice;
    QButtonGroup active;
    QButtonGroup refine;
    QButtonGroup buy;
    QButtonGroup compose;
    
    QButtonGroup players;
    int adventureRefine();
public:
    ActiveDialog(PaintStruct*,QWidget* parent);
    void getActivatedSkill(int characterNum,int& skill1, int& skill2);
    bool canActivate(int characterNum, int skill);
    int getActivatedNum(int characterNum);
public slots:
    void ensureClicked();
    void cancelClicked();
};

class CureDialog : public AskDialog
{
    Q_OBJECT
    QButtonGroup cure;
public:
    CureDialog(int damage, PaintStruct*,QWidget* parent);
public slots:
    void ensureClicked();
    void cancelClicked();
};

class NumberDialog : public AskDialog
{
    Q_OBJECT
    QButtonGroup cure;
public:
    PicButton* number[5];
    NumberDialog(PaintStruct*,QWidget* parent);
    public slots:
    void ensureClicked();
    void cancelClicked();
};

class SpecialDialog : public AskDialog
{
    Q_OBJECT
public:
    SpecialDialog(PaintStruct*, QWidget* parent);
public slots:
    void ensureClicked();
    void cancelClicked();
};

#endif // ASKDIALOG_H
