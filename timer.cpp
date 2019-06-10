#include "timer.h"
#include "ui_timer.h"
#include <QTimer>
Timer::Timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    this->setWindowTitle("Resuming Game");

    timer = startTimer(1000);
}

Timer::~Timer()
{
    delete ui;
}
void Timer::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);
    ui->label->setText(QString::number(count));
    if(count == 0){
        this->close();
    }
    count--;
}

void Timer::on_pushButton_clicked()
{
    this->close();
}
