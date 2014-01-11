#include "picbutton.h"
#include <cstdlib>
#include <QString>
#include <iostream>
PicButton::PicButton(/*int buttonKind,*/int paraX,int paraY,int paraW,int paraH,bool canBe,QWidget* parent) : QPushButton(parent)
{
    setCheckable(true);
    setChecked(false);
    setEnabled(canBe);
    setGeometry(paraX, paraY, paraW, paraH);
    setMinimumSize(paraW, paraH);
    clickedLabel.setParent(this);
    notClickedLabel.setParent(this);
    frameLabel.setParent(this);
    clickedLabel.setGeometry(0, 0, paraW, paraH);
    notClickedLabel.setGeometry(0, 0, paraW, paraH);
    frameLabel.setGeometry(0, 0, paraW, paraH);
    this->setStyleSheet("border:none;");
    
//    QString s;
//    kind = buttonKind;
//    s.sprintf(":/button/buttonNotClicked%d.png",buttonKind);
//    notClickedMap = new QPixmap();
//    notClickedMap->load(s);
//    clickedMap = new QPixmap();
//    if(buttonKind < 25)
//    {
//        s.sprintf(":/character/character%d.png",buttonKind);
//        //system("pause");
//        clickedMap->load(s);
//        notClickedMap->load(s);
//    }
//    else
//    {
//        s.sprintf(":/button/buttonClicked%d.png",buttonKind);
//        clickedMap->load(s);
//    }
    
//    switch(paraW)
//    {
//        case 100:
//        {
//            s.sprintf(":/character/buttonFrame100.png");
//            break;
//        }
//        case 50:
//        {
//            if(paraH == 42)
//            {
//                s.sprintf(":/character/buttonFrame50.png");
//                break;
//            }
//            else
//            {
//                s.sprintf(":/character/cureFrame.png");
//            }
//        }
//        case 48:
//        {
//            s.sprintf(":/character/cardFrameX.png");
//        }
//        default:
//        {
//            s.sprintf(":/character/choosenFrame.png");
//        }
//    }
//    frame = new QPixmap(":/character/buttonFrame100.png");
//    frame->load(s);
//    clickedLabel.setPixmap(*clickedMap);
//    notClickedLabel.setPixmap(*notClickedMap);
//    frameLabel.setPixmap(*frame);
    
    //notClickedLabel.setPixmap(QPixmap(":/character/buttonFrame100.png"));
    clickedLabel.setVisible(false);
    notClickedLabel.setVisible(true);
    frameLabel.setVisible(false);
    connect(this, SIGNAL(clicked()), this, SLOT(isThisClicked()));
    show();
}//buttonKind from 1 to 31:For characterPic;

PicButton::PicButton(int n,int paraX,int paraY,int paraW,int paraH,bool canBe,QWidget* parent) : QPushButton(parent)
{
    setCheckable(true);
    setChecked(false);
    setEnabled(canBe);
    setGeometry(paraX, paraY, paraW, paraH);
    setMinimumSize(paraW, paraH);
    clickedLabel.setParent(this);
    notClickedLabel.setParent(this);
    frameLabel.setParent(this);
    clickedLabel.setGeometry(0, 0, paraW, paraH);
    notClickedLabel.setGeometry(0, 0, paraW, paraH);
    frameLabel.setGeometry(0, 0, paraW, paraH);
    this->setStyleSheet("border:none;");

    clickedLabel.setVisible(false);
    notClickedLabel.setVisible(true);
    frameLabel.setVisible(false);
    connect(this, SIGNAL(clicked()), this, SLOT(isThisClicked()));
    
    setByNumber(n);
    show();
}


void PicButton::setNumber(int n)
{
    notClickedLabel.setPixmap(QPixmap(QString(":button/buttonNotClicked%1.png").arg(QString::number(n+48))));
    clickedLabel.setPixmap(QPixmap(QString(":button/buttonClicked%1.png").arg(QString::number(n+48))));
    frameLabel.setPixmap(QPixmap(":character/cureFrame.png"));

}

void PicButton::setRefine(int n)
{
    notClickedLabel.setPixmap(QPixmap(QString(":button/buttonNotClicked%1.png").arg(QString::number(n+38))));
    clickedLabel.setPixmap(QPixmap(QString(":button/buttonClicked%1.png").arg(QString::number(n+38))));
    frameLabel.setPixmap(QPixmap(":character/buttonFrame100.png"));
}

void PicButton::setByNumber(int n)
{
    notClickedLabel.setPixmap(QPixmap(QString(":button/buttonNotClicked%1.png").arg(QString::number(n))));
    clickedLabel.setPixmap(QPixmap(QString(":button/buttonClicked%1.png").arg(QString::number(n))));
    if (n>54||n<48) {
        frameLabel.setPixmap(QPixmap(":character/buttonFrame100.png"));
    }

}

void PicButton::isThisClicked()
{
    if(isChecked())
    {
        emit beChecked();
    }
    else
    {
        emit unChecked();
    }
}
void PicButton::paintEvent(QPaintEvent *event)
{
    if(isChecked())
    {
        clickedLabel.setVisible(true);
        notClickedLabel.setVisible(false);
        frameLabel.setVisible(true);
    }
    else
    {
        clickedLabel.setVisible(false);
        notClickedLabel.setVisible(true);
        frameLabel.setVisible(false);
    }
}
//void PicButton::cancelX()
//{
    //setChecked(false);
//}
//void PicButton::recover()
//{
//    //setChecked(true);
//}
//void PicButton::setCheckableFals(bool state)
//{
//    setEnabled(state);
//}
void PicButton::setCheckableFalse()
{
    //setEnabled(false);
    setCheckable(false);
    //setChecked(false);
    //isClicked  = false;
}
void PicButton::setCheckedFalse()
{
    //setEnabled(false);
    setChecked(false);
    //isClicked  = false;
}
void PicButton::setCheckedTrue()
{
    //setEnabled(false);
    setChecked(true);
    //isClicked  = false;
}
void PicButton::setCheckableTrue()
{
    //setEnabled(true);
    setCheckable(true);
}
