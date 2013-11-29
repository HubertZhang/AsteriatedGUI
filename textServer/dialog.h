#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "agserver.h"
#include "chatserver.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    AGServer server;
    AGChatServer chatServer;
public slots:
    void send();
    void begin();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
