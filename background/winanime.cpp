#include "winanime.h"
#include <QString>
WinAnime::WinAnime(QWidget *parent) :
QPushButton(parent)
{
    this->setMinimumSize(300,100);
    this->move(533,334);
    this->setStyleSheet("border:none");
    this->setStyleSheet("background-color:transparent");
    winPic = new QPixmap();
}
void WinAnime::setPic()
{
    if(winTeam)
    {
        winPic->load(":/end/redWin.png");
    }
    else
    {
        winPic->load(":/end/blueWin.png");
    }
    this->setIcon(*winPic);
    this->setIconSize(QSize(300,100));
    this->show();
}

