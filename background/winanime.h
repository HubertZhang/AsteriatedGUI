#ifndef WINANIME_H
#define WINANIME_H

#include <QPushButton>
#include <QPixmap>
#include <QPainter>

class WinAnime : public QPushButton
{
    Q_OBJECT
private:
    QPixmap* winPic;
public:
    bool winTeam;
    void setPic();
    explicit WinAnime(QWidget *parent = 0);
    void paint(QPaintEvent* event,QPainter* painter);

public slots:

};

#endif // WINANIME_H
