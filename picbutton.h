#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QLabel>
class PicButton : public QPushButton
{
    Q_OBJECT
//    QPixmap* clickedMap;
//    QPixmap* notClickedMap;
//    QPixmap* frame;
    
public:
    QLabel clickedLabel;
    QLabel notClickedLabel;
    QLabel frameLabel;
//    bool isClicked;
//    bool canBeClicked;
    int xp;
    int yp;
    int kind;
    int width;
    int height;
    void setNumber(int n);
    void setRefine(int n);
    void setByNumber(int n);
    PicButton(/*int buttonKind,*/int paraX,int paraY,int paraW,int paraH,bool canbe,QWidget* parent);//buttonKind decide the pic to load
    PicButton(int n,int paraX,int paraY,int paraW,int paraH,bool canBe, QWidget* parent);
protected:
    void paintEvent(QPaintEvent* event);
signals:
    void beChecked();
    void unChecked();
public slots:
    void isThisClicked();
    void setCheckableFalse();
    void setCheckableTrue();
    void setCheckedFalse();
    void setCheckedTrue();
    //void setState(bool);
};
#endif // PICBUTTON_H
