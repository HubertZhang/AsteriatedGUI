#ifndef ASKDIALOG_H
#define ASKDIALOG_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include "picbutton.h"
#include "paintstruct.h"
class Window;
class AskDialog : public QWidget
{
    Q_OBJECT
public:
    Window* storeWindow;
    QString s;
    QPixmap* bg;
    PicButton* ensure;
    PicButton* cancel;
    QFont* font;
    QLabel* labelOne;
    QLabel* labelTwo;
    QPalette* palette;
    PaintStruct* storeData;
    PicButton* attributeGroup[4];
    PicButton* activateGroup[2];
    PicButton* refineGroup[5];
    PicButton* buyGroup[4];
    PicButton* composeGroup[4];
    PicButton* number[5];
    int actNum;
    bool redWhite;
    int informationKind;
    int getActivatedNum(int characterNum);
    void activeInit(int characterNum);
    void paint(QPaintEvent*,QPainter*);
    bool canActivate(int skillNum);
    explicit AskDialog(int information[3],Window *parent,PaintStruct*,bool redWhiteLink);
    ~AskDialog();
    int kind[3];
signals:
    void sendMessageSpeSig(std::vector<int>);
    void sendMessageWeakSig(std::vector<int>);
    void sendMessageCureSig(std::vector<int>);
public slots:
    void destroyLabel();
    void sendMessageSpe();
    void sendMessageWeak();
    void sendMessageCure();
    void sendMessageAskDialog();
    void adventureRefine();
    void adventureReset();
};

#endif // ASKDIALOG_H
