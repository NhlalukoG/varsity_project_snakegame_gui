#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowTitle("Help");
    ui->textBrowser->setStyleSheet("border:1px solid black;border-radius:2px;background-color:rgba(155,155,155,0.5)");
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    this->close();
}
