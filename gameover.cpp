#include "gameover.h"
#include "ui_gameover.h"
#include "startscreen.h"
#include "mainwindow.h"
#include "highscore.h"
#include <QMessageBox>
#include <QInputDialog>
Gameover::Gameover(QWidget *parent, int eaten,QString tym,bool mode) :
    QWidget(parent),
    ui(new Ui::Gameover)
{
    this->setWindowTitle("Game Over");
    playmode=mode;
    ui->setupUi(this);
    ui->label_2->setText(QString::number(eaten));
    ui->label_4->setText(tym);
    //qDebug() << parent->height();
}

Gameover::~Gameover()
{
    delete ui;
}

void Gameover::on_pushButton_clicked()
{
    qDebug() << childrenRect().height();
    //game->SetScene("");
    this->close();
}

void Gameover::on_pushButton_2_clicked()
{

    StartScreen *window = new StartScreen;
    window->show();
    this->close();

}

void Gameover::on_pushButton_3_clicked()
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

void Gameover::on_pushButton_4_clicked()
{
    QFile handle("/home/nhlaluko/data.bin");

    //if(handle.isReadable() && handle.isWritable()){
        /*We can use the file*/
        handle.open(QFile::WriteOnly);

        QTextStream stream(&handle);

        stream << "Test";

        stream.flush();

    //}else{
    //    ui->textEdit->setText("OOOOPPPPSSSSSSSSSSSSSS");
    //}
}
