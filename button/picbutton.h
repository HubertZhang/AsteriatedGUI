#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
class PicButton : public QWidget
{
    Q_OBJECT
public:
    QPixmap* clickedMap;
    QPixmap* notClickedMap;
    QPixmap* frame;
    bool isClicked;
    bool canBeClicked;
    int xp;
    int yp;
    int kind;
    int width;
    int height;
    explicit PicButton(int buttonKind,int paraX,int paraY,int paraW,int paraH,bool canbe);//buttonKind decide the pic to load
    void paint(QPaintEvent*,QPainter*);
    void paintCharacter(QPaintEvent*,QPainter*);
signals:
    void changeClicked();
    void notClicked();
public slots:
    void isThisClicked(int x,int y);
    void cancelX();
    void recover();
    void cancelClick();
    void recoverClick();
};
#endif // PICBUTTON_H
