#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QWidget>
#include "picbutton.h"
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QPalette>

class NewDialog : public QLabel
{
    Q_OBJECT
public:
    explicit NewDialog(QWidget*);
    void init(int);
    int skillCount;
    QFont* font;
    QPalette* palette;
    QLabel* label;
    PicButton* skillGroup[10];
    void set(bool canX[10]);
signals:

public slots:

};

#endif // NEWDIALOG_H
