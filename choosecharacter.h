#ifndef CHOOSECHARACTER_H
#define CHOOSECHARACTER_H
#include <QButtonGroup>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include "characterbutton.h"
class ChooseCharacter : public QLabel
{
    Q_OBJECT
public:
    QButtonGroup characters;
    QPixmap* bg;
    CharacterButton* character[3];
    PicButton* ensure;
    PicButton* cancel;
//    QPixmap* choose;
    explicit ChooseCharacter(int numOne,int numTwo,int numThree,QWidget *parent = 0);
//    void paint(QPaintEvent* event,QPainter* painter);
//    ~ ChooseCharacter();
signals:
    void sendMessageChooseSig(std::vector<int>);
public slots:
    //void sendMessageChoose();
    void recover();
    void sendMessage();
};

#endif // CHOOSECHARACTER_H
