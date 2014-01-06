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
//    int xp;
//    int yp;
//    int kind;
//    int width;
//    int height;
    explicit PicButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canbe);//buttonKind decide the pic to load
protected:
    void paintEvent(QPaintEvent* event);
signals:
    void changeClicked();
    void notClicked();
public slots:
    void isThisClicked();
    void cancelX();
    void recover();
    void cancelClick();
    void recoverClick();
};
#endif // PICBUTTON_H
