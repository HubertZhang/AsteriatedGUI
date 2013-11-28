#ifndef MESSAGESOURCE_H
#define MESSAGESOURCE_H

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
class MessageSource : public QWidget
{
    Q_OBJECT
private:
    QPushButton* submit;
public:
    explicit MessageSource(QWidget *parent = 0);
    QLineEdit* inputLine;
signals:
    void buttonClicked();
public slots:
    void isClicked();
};

#endif // MESSAGESOURCE_H
