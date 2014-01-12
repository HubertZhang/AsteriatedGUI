#ifndef MESSAGESOURCE_H
#define MESSAGESOURCE_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QLabel>
class MessageSource : public QDialog
{
    Q_OBJECT
private:
    bool flag;
    QPushButton* submit;
public:
    explicit MessageSource(QWidget *parent = 0);
    QLineEdit* inputLine;
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void buttonClicked();
public slots:
    void isClicked();
};

#endif // MESSAGESOURCE_H
