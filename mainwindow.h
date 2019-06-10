#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <vector>
#include <iostream>
#include "QDebug"
#include <sstream>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QTextBrowser>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QSlider>
#include <QRadioButton>
#include <QLineEdit>

/*Sound*/

#include <QtMultimedia>
//#include <phonon/phonon>


/*Scene Screens*/
//#include "snake.h"
#include "startscreen.h"
#include "paused.h"
#include "gameover.h"
#include "highscore.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,bool mode = false);
    ~MainWindow();
    /*Custom Functions*/

protected:
    //void keyPressEvent();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer2;
    bool off;
    int hr,mn,sc,dl;
    QString title;
    QPushButton *button;

    std::vector<QGraphicsPixmapItem*> gdots;
    QGraphicsPixmapItem* gapple;
    QGraphicsPixmapItem* bonusapple;
    QGraphicsPixmapItem* orange_block;
    QGraphicsPixmapItem* grey_block;

    /*sound*/
    QMediaPlayer *player;
    QMediaPlayer *effect;

    /*Game Scenes*/
    QGraphicsScene* gscene;     //game scene
    QGraphicsScene* startscreen; //StartScreen scene
    QGraphicsScene* PauseScene; //Pause screen scene
    QGraphicsScene* OptionScene; //Settings screen scene
    QGraphicsScene* helpscene;  //Help Screen scene
    QGraphicsScene* highscorescene; //High Score screen
    QGraphicsScene* gameoverscene; //High Score screen
    QGraphicsScene* aboutscene; //High Score screen

    QString username = "";

    int B_WIDTH;
    int B_HEIGHT;
    static const int DOT_SIZE = 20;
    static const int ALL_DOTS = 900;
    int RAND_POS;
    int DELAY = 100;

    int duration;
    int apples;
    int mystage = 9;
    int highscore = 0;
    int scorer = 0;
    int points = 0;

    //int timerId;
    int dots;
    int apple_x;
    int apple_y;
    int bonus_x;
    int bonus_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    int x_temp[ALL_DOTS];
    int y_temp[ALL_DOTS];

    int obstacle_x[20];
    int obstacle_y[20];
    int corner_x[80];
    int corner_y[80];

    bool leftDirection = false;
    bool rightDirection = true;
    bool upDirection = false;
    bool downDirection = false;
    bool inGame;
    bool ghost;
    bool isFree = false; //will only be change if the stage enter from the slide show is in the range require

    /*Game attributes*/
    /*Old Functions*/
    void loadImages();
    void initGame();
    void locateApple();

    void positionApple();//generate a new random apple_x and apple_y.
    void checkIfAppleEaten();
    void checkCollision();
    void move();
    void render();//update the scene based on current positions i.e apple_x, apple_y,x and y.
    void gameOver();

    /*Custom variables*/
    bool pausedsdsdsd = false;
    bool playMode;
    bool bonus;
    int current_stage = 0;





    /***********************Options Screen**************************************/
     QSlider *volume_slider;
     QSlider *Game_Speed;
     QSlider *Game_Level;
     QPushButton *save;
     QLabel *set_speed,*set_level;
     /***************************Game Scene*************************************/

     QLabel *score;
     QLabel time;
     QLabel *ptimer;
     QLineEdit *edit;

private slots:





    bool SetScene();
    bool viewHelp();
    bool viewAbout();
    bool Resume();
    bool newGame();
    bool watchGame();
    bool viewHighScore();
    bool goHome();
    bool exitOnClos();
    bool viewOption();
    bool savesettings();
    void speedchanged(int speed = 100);
    void levelchanged(int level = 0);
    bool savegameresult();
    bool savegame();



    void tick();//updates digital watch
    void pause();//connected to pushButton. Called every time it is pressed.
    void timerEvent();//connected to timer. Called every DELAY milliseconds, controls MainWindow movement and digital watch.
    void keyPressEvent(QKeyEvent *event);
    void getMoveDirection(QString);
    void getAutoDirection();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
