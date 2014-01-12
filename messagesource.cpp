#include "messagesource.h"
#include <QVBoxLayout>
MessageSource::MessageSource(QWidget *parent)
    : QDialog(parent)
{
    flag = false;
    submit = new QPushButton("submit",this);
    connect(submit,SIGNAL(clicked()),this,SLOT(isClicked()));
    inputLine = new QLineEdit(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* pic = new QLabel(this);
    pic->setPixmap(QPixmap(":/Icon.png"));
    QLabel* text = new QLabel(this);
    text->setText("请输入服务器IP:");
    layout->addWidget(pic);
    layout->addWidget(text);
    layout->addWidget(inputLine);
    layout->addWidget(submit);
    setLayout(layout);
}
void MessageSource::isClicked()
{
    flag = true;
    emit buttonClicked();
}
void MessageSource::closeEvent(QCloseEvent *event)
{
    if(flag)
    {
        setResult(1);
    }
    else setResult(0);
}
