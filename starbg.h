#ifndef STARBG_H
#define STARBG_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>

class StarBG : public QLabel
{
    Q_OBJECT
private:
    bool sign;
    int frame;
    int refreshSpeed;
    QPixmap starBGArray[40];
public:
    explicit StarBG(QWidget *parent = 0);
    void update();
public slots:

};

#endif // STARBG_H
