#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>
#include <QLabel>
class PicButton : public QPushButton
{
    Q_OBJECT
public:
    QPixmap* clickedMap;
    QPixmap* notClickedMap;
    QPixmap* frame;
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
    explicit PicButton(/*int buttonKind,*/int paraX,int paraY,int paraW,int paraH,bool canbe,QWidget* parent);//buttonKind decide the pic to load
signals:
    void beChecked();
    void unChecked();
public slots:
    void isThisClicked();
    void enable();
    void disable();
    void setState(bool);
};
#endif // PICBUTTON_H
