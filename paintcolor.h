#ifndef PAINTCOLOR_H
#define PAINTCOLOR_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
class PaintColor : public QWidget
{
    Q_OBJECT
private:
    QPixmap* redFrame;
    QPixmap* blueFrame;
    QPixmap* frame;
    int xp[6];
    int yp[6];
    int width;
    int height;
    int pColor[6];
public:
    explicit PaintColor(int color[5],QWidget *parent = 0);
    void paint(QPaintEvent *event,QPainter* painter);
signals:

public slots:

};

#endif // PAINTCOLOR_H
