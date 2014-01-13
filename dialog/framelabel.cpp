#include "framelabel.h"

FrameLabel::FrameLabel(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(1366,768);
    font = new QFont();
    font->setPointSize(30);
    font->setBold(true);
    palette = new QPalette();
    palette->setColor(QPalette::WindowText,Qt::yellow);
    labelOne = new QLabel(parent);
    labelTwo = new QLabel(parent);
    labelOne->setFont(*font);
    labelOne->setPalette(*palette);
    labelTwo->setFont(*font);
    labelTwo->setPalette(*palette);
    labelOne->setMinimumSize(500,100);
    labelTwo->setMinimumSize(500,100);
    frame = new QPixmap();
    frame->load(":/character/chooseCharacterFrame.png");
}
void FrameLabel::reset()
{
    delete labelOne;
    delete labelTwo;
}
void FrameLabel::paint(QPaintEvent *event, QPainter *painter)
{
    painter->drawPixmap(328,247,frame->width(),frame->height(),*frame);
    labelOne->move(328 + 25,247 - 10);
    labelTwo->move(328 + 25,247 + 30);
    labelOne->show();
    labelTwo->show();
}
