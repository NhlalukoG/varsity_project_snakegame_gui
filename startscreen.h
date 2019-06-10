#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include "mainwindow.h"
#include "help.h"
#include "highscore.h"
namespace Ui {
class StartScreen;
}

class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = 0);
    ~StartScreen();
    static bool selfPlay;

private slots:
    void on_pushButton_clicked();
    void showmain();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StartScreen *ui;
    //HighScore *score;
};

#endif // STARTSCREEN_H

