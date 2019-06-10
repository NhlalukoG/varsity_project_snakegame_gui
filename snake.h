#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QDialog>
#include <QTextStream>
class Snake : public QWidget {

  public:
      Snake(QWidget *parent = 0,bool mode = false);
      ~Snake();

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);
  private slots:
      void update();
  private:
      QImage dot;
      QImage head;
      QImage apple;

      static const int B_WIDTH = 300;
      static const int B_HEIGHT = 300;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 900;
      static const int RAND_POS = 29;
      static const int DELAY = 100;

      int timerId;
      int dots;
      int apple_x;
      int apple_y;

      int sc = 0,mn = 0,hr = 0;
      QString tym = "00:00:00";
      int eaten = 0;
      QTimer *timer;
      QTime time;

      int x[ALL_DOTS];
      int y[ALL_DOTS];

      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame; // Check to see if game is over (true = playing, false = collided)
      bool pause = false;
      bool playMode;

      void loadImages();
      void initGame();
      void locateApple();   // Randomnly puts an apple to a location
      void checkApple();
      void checkCollision();
      void move();
      void doDrawing();
      void gameOver();
      void selfPlay();

      void getMoveDirection(QString);
      void getAutoDirection();
      void stage1();
      void stage2();
      void stage3();
      void stage4();

};
#endif // SNAKE_H
