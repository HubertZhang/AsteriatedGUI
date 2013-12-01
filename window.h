#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTimer>
#include "starbg.h"
#include "paintstruct.h"
#include "messagesource.h"
#include "paintcolor.h"
#include "choosecharacter.h"
#include <QMouseEvent>
#include "askdialog.h"
#include "agclient.h"
#include "agchatclient.h"
#include "cardList.h"
#include "cardandskill.h"
#include "cardattack.h"
#include "swordmaster.h"
#include "berserker.h"
#include "arrowmaid.h"
#include "sealmaid.h"
#include "darkkiller.h"
#include "puremaid.h"
#include "angel.h"
#include "magicmaid.h"
#include "magicsword.h"
#include "purespear.h"
#include "elementmaster.h"
#include "adventurer.h"
#include "necromancer.h"
#include "arbitrationmaid.h"
#include "priestmaid.h"
class Window : public QWidget
{
    Q_OBJECT
private:
    QTimer* timer;
    StarBG* starBG;
    PaintStruct* paintStruct;
    MessageSource* mySource;
    PaintColor* wColor;
    ChooseCharacter* chooseCharacter;
    AskDialog* askDialog;
    CardList* cardList;
    CardAndSkill* cardAndSkill;
    CardAttack* cardAttack;
    int paintStructInit[15];
    int phase;//To decide the paint function
    bool paint;
public:
    QLineEdit* chatLine;
    QTextBrowser* chatBrowser;
    explicit Window(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    AGClient networkSocket;
    AGChatClient chatSocket;
protected:
    void paintEvent(QPaintEvent *);
public slots:
    void timeOut();
    void informationGet();
    void messageProcess(std::vector<int> m);
    void chatReady(int id);
    void sendChatMessage();
    void displayMessage(int id,QString message);
    void changeWPhase();
    void changeXPhase();
    void changeYPhase();
    void changeZPhase();
signals:
    void mouseClicked(int x,int y);
};


#endif // WINDOW_H
