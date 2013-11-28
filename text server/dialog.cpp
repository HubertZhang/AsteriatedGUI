#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),server(parent,1)
{
    ui->setupUi(this);
    //connect(ui->lineEdit,SIGNAL(returnPressed()),ui->pushButton,SLOT(click()));
    connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(send()));
    connect(&server,SIGNAL(connectionBuilt()),this,SLOT(begin()));
    ui->pushButton->setEnabled(false);
}

void Dialog::begin()
{
    ui->pushButton->setEnabled(true);
    ui->label->setText(QString("connected."));
}

void Dialog::send()
{
    QString temp = ui->lineEdit->text();
        ui->lineEdit->clear();
        QTextStream textout(&temp);
        vector<int> message;
        while(!textout.atEnd())
        {
            int t;
            textout >> t;
            message.push_back(t);
        }
        server.sendMessage(0,message);
}
Dialog::~Dialog()
{
    delete ui;
}
