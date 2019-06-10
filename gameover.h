#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
//#include "MainWindow.h"
#include "highscore.h"
#include <QFile>
#include <QTextStream>

namespace Ui {
class Gameover;
}

class Gameover : public QWidget
{
    Q_OBJECT

public:
    explicit Gameover(QWidget *parent = 0,int eaten = 0,QString tym = "00:00:00",bool mode=false);
    ~Gameover();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Gameover *ui;
    bool playmode;
    HighScore *score;
};

#endif // GAMEOVER_H
