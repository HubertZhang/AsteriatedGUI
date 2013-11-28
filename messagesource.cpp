#include "messagesource.h"
#include <QVBoxLayout>
MessageSource::MessageSource(QWidget *parent)
    : QWidget(parent)
{
    submit = new QPushButton("submit");
    connect(submit,SIGNAL(clicked()),this,SLOT(isClicked()));
    inputLine = new QLineEdit();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(inputLine);
    layout->addWidget(submit);
    setLayout(layout);
    resize(200,200);
    this->show();
}
void MessageSource::isClicked()
{
    emit buttonClicked();
}
