#include "messagesource.h"
#include <QVBoxLayout>
MessageSource::MessageSource(QWidget *parent)
    : QDialog(parent)
{
    submit = new QPushButton("submit");
    connect(submit,SIGNAL(clicked()),this,SLOT(isClicked()));
    inputLine = new QLineEdit();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(inputLine);
    layout->addWidget(submit);
    setLayout(layout);
    resize(200,200);
}
void MessageSource::isClicked()
{
    emit buttonClicked();
}
