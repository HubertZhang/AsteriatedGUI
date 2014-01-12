#ifndef FRAMELABEL_H
#define FRAMELABEL_H

#include <QWidget>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QPalette>
class Window;
class FrameLabel : public QWidget
{
    Q_OBJECT
public:
    explicit FrameLabel(QWidget *parent);
    QLabel* labelOne;
    QLabel* labelTwo;
    QPixmap* frame;
    QFont* font;
    QPalette* palette;
    void paint(QPaintEvent *event,QPainter* painter);
    void reset();
signals:

public slots:

};

#endif // FRAMELABEL_H
