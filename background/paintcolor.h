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
    QPainter* Frame;
public:
    explicit PaintColor(int color[6],QWidget* parent);
protected:
    void paintEvent(QPaintEvent* event);
signals:

public slots:

};

#endif // PAINTCOLOR_H
