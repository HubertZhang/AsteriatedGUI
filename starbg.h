#ifndef STARBG_H
#define STARBG_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

class StarBG : public QWidget
{
    Q_OBJECT
private:
    bool sign;
    int frame;
    int refreshSpeed;
    QPixmap* starBGArray[40];
public:
    explicit StarBG(QWidget *parent = 0);
    void paint(QPaintEvent *,QPainter* painter);
public slots:

};

#endif // STARBG_H
