#include "highscore.h"
#include "ui_highscore.h"
#include <QFile>
#include <QTextStream>
HighScore::HighScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScore)
{

    ui->setupUi(this);
    this->setWindowTitle("High Scores...");
    QFile file("data.bin");
    if(file.exists()){
            file.open(QFile::ReadOnly);
            QTextStream data(&file);
            ui->textBrowser->setText(data.readAll());
    }else{
        ui->textBrowser->setText("Play some games first");
    }
}

HighScore::~HighScore()
{
    delete ui;
}

void HighScore::on_pushButton_clicked()
{
    this->close();
}
