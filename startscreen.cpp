#include "startscreen.h"
#include "ui_startscreen.h"
#include "about.h"
#include "help.h"
#include <QMessageBox>
StartScreen::StartScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    this->setWindowTitle("MainWindow Game");
    this->setStyleSheet("background-image:url(\":/images/bg.jpg\");background-position: stretch;background-image: no-repeat;");
    ui->pushButton->setStyleSheet("border:2px solid white;border-radius:10px;background:grey;color:white;");
    ui->pushButton_2->setStyleSheet("border:2px solid white;border-radius:10px;background:grey;color:white;");
    ui->pushButton_3->setStyleSheet("border:2px solid white;border-radius:10px;background:grey;color:white;");
    ui->pushButton_4->setStyleSheet("border:2px solid white;border-radius:10px;background:grey;color:white;");
    ui->pushButton_5->setStyleSheet("border:2px solid white;border-radius:10px;background:grey;color:white;");
    ui->pushButton_6->setStyleSheet("border:2px solid white;border-radius:10px;background:grey;color:white;");
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::on_pushButton_clicked()
{

}
void StartScreen::showmain(){
    this->show();
}

void StartScreen::on_pushButton_4_clicked()
{
    About *about = new About;
    about->setModal(true);
    about->exec();
}

void StartScreen::on_pushButton_5_clicked()
{
    this->hide();

}

void StartScreen::on_pushButton_3_clicked()
{
    Help *help = new Help;
    help->exec();
}

void StartScreen::on_pushButton_6_clicked()
{
    QMessageBox *confirm = new QMessageBox;
    confirm->setWindowTitle("Confirm Quit");
    confirm->setText("Are you sure you want to exit the game?");

    confirm->setStandardButtons(QMessageBox::Yes);
    confirm->addButton(QMessageBox::No);
    confirm->setDefaultButton(QMessageBox::No);

    ;
    if(confirm->exec() == QMessageBox::Yes){
        this->close();
    }else{

    }
}

void StartScreen::on_pushButton_2_clicked()
{

}
