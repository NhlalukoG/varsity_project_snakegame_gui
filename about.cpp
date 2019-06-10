#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->textEdit->setStyleSheet("border:1px solid black;border-radius:2px;background-color:rgba(155,155,155,0.5)");

    this->setWindowTitle("About MainWindow");

}

About::~About()
{
    delete ui;

}
