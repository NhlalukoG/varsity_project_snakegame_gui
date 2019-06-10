#ifndef TIMER_H
#define TIMER_H

#include <QDialog>

namespace Ui {
class Timer;
}

class Timer : public QDialog
{
    Q_OBJECT
protected:
    void timerEvent(QTimerEvent *e);
public:
    explicit Timer(QWidget *parent = 0);
    ~Timer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Timer *ui;
    int timer;
    int count = 5;
};

#endif // TIMER_H
