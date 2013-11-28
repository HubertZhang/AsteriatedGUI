#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QWidget>
#include "picbutton.h"
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QPalette>

class NewDialog : public QWidget
{
    Q_OBJECT
public:
    explicit NewDialog(QWidget *parent = 0);
    void init(int);
    int skillCount;
    QFont* font;
    QPalette* palette;
    QLabel* label;
    QPixmap* frame;
    PicButton* skillGroup[10];
    void set(bool canX[10]);
    void paint(QPaintEvent *,QPainter *);
signals:

public slots:

};

#endif // NEWDIALOG_H
