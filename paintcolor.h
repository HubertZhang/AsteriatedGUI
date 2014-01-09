#ifndef PAINTCOLOR_H
#define PAINTCOLOR_H

#include "placeinfo.h"
#include <QLabel>
#include <QPixmap>

class PaintColor : public QLabel
{
    Q_OBJECT
private:
    //QLabel* redFrame;
    //QLabel* blueFrame;
    QLabel frame;
    QLabel playerFrame[6];
    //int xp[6];
    //int yp[6];
    //int width;
    //int height;
    //int pColor[6];
    //QPainter* Frame;
public:
    explicit PaintColor(int color[6],QWidget* parent);
protected:
    //void paintEvent(QPaintEvent* event);
signals:

public slots:

};

#endif // PAINTCOLOR_H
