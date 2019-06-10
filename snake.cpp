#include <QPainter>
#include <QTime>
#include "snake.h"
#include "startscreen.h"
#include "paused.h"
#include "gameover.h"
#include <sstream>

Snake::Snake(QWidget *parent,bool mode) : QWidget(parent) {
    playMode = mode;
    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    playMode = mode;
    resize(B_WIDTH, B_HEIGHT);
    loadImages();

    // Timer to calculate game play
    timer = new QTimer(this);
    // Start game
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);
    initGame();
}
Snake::~Snake(){
    StartScreen *x = new StartScreen;
    x->show();
    delete this;
}

void Snake::update(){
        sc++;
        if(sc==60){
            mn++;
            sc=0;
        }
        if(mn==60){
            hr++;
            mn=0;
        }
        if(hr==24)
            hr=0;
        std::stringstream ss;
        if(hr<10)
              ss<<0<<hr<<":";
        else
            ss<<hr<<":";
        if(mn<10)
            ss<<0<<mn<<":";
        else
            ss<<mn<<":";
        if(sc<10)
            ss<<0<<sc;
        else
            ss<<sc;
        QString qs(ss.str().c_str());
        tym = qs;
}

void Snake::loadImages() {
    dot.load(":/images/dot.png");
    head.load(":/images/head.png");
    apple.load(":/images/apple.png");
}

void Snake::initGame() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();
    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e) {
    // When the screen is changed
    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {
    // Set the snake on its places as it moves
    QPainter qp(this);

    if (inGame) {
        // While the game is still in play
        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {
        // print the gameover screen
        gameOver();
    }
}

void Snake::gameOver() {
    // Game over screen

    // Write High Score to file

    QFile file("data.bin");

    file.open(QFile::WriteOnly);

    QTextStream write(&file);


    write << "blaaaa";

    /*QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);
    qp.setFont(font);
    int h = height();
    int w = width();
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);*/
    Gameover *gamey = new Gameover(0,eaten,tym,playMode);
    gamey->show();
    this->close();

}

void Snake::checkApple() {
    // Check to see if an apple is eaten
    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        // If the apple has been eaten increase snake size
        dots++;
        eaten++;
        // randomly place apple
        locateApple();
    }
}

void Snake::move() {
    // The snake can only move to one direction a time
    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {
    // If inGame is false, this means collision
    /*if(playMode){
        // Collision management for self playing game
    }else{*/
        // Collision management for game play
        for (int z = dots; z > 0; z--) {
            if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                inGame = false;
            }
        }
        if (y[0] >= B_HEIGHT) {
            // If colided(higher than) with the top
            inGame = false;
        }

        if (y[0] < 0) {
            inGame = false;
        }

        if (x[0] >= B_WIDTH) {
            // If colided(past over) with the sides
            inGame = false;
        }

        if (x[0] < 0) {
            inGame = false;
        }

    if(!inGame) {
        // If inGame is false.
        // This means if the player has terminated the snake
        killTimer(timerId);
    }
}

void Snake::locateApple() {
    // Place Apple randomly
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);
    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
    for(int i = 0;i < dots;i++){
        // Loop thorough the body of the same and search for the apple
        if(x[i] == apple_x && y[i] == apple_y){
            int r = qrand() % RAND_POS;
            apple_x = (r * DOT_SIZE);
            r = qrand() % RAND_POS;
            apple_y = (r * DOT_SIZE);
            // If the apple is inside the body of the snake, place it again
            //locateApple();
        }
        //else{
            //continue and check the rest of the snake
           // continue;
        //}
    }

}

void Snake::timerEvent(QTimerEvent *e) {
    // Runs by default at the event of time change
    Q_UNUSED(e);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    if (inGame) {
        // If the snake hasnt died yet

        if(playMode){
            // If the game was told to self play
            checkApple();
            getAutoDirection();
            checkCollision();
            move();
        }else{
            checkApple();       // Place apple randomly
           stage2(); // Check if the snake has collided to stop the game
            move();             // Move the snake
        }
    }
    // Puts the snake on the screen or display game over text
    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {
    // In events where keys are pressed
    int key = e->key();
    /* The Snake cannot go the opposite the direction at will
     * The snake must first make a right angled turn
     * And the snake can only go to one direction at a time
     * (Only one direction is true)
     */
    if (((key == Qt::Key_Left) || (key == Qt::Key_A)) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if (((key == Qt::Key_Right) || (key == Qt::Key_D))  && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if (((key == Qt::Key_Up) || (key == Qt::Key_W)) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if (((key == Qt::Key_Down) || (key == Qt::Key_S)) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
    if (key == Qt::Key_Space || key == Qt::Key_Escape) {
        killTimer(timerId);
        timer->stop();
        pause = true;
        paused *gamepause = new paused(0,eaten,tym,playMode,this);
        gamepause->exec();
        timer->start();
        timerId = startTimer(DELAY);
    }
    QWidget::keyPressEvent(e);
}

void Snake::getAutoDirection(){
    // Check horizontal position
    if (x[0] < apple_x) {
        for (int z = dots; z > 0; z--) {
            if (!((z > 4) && (x[0]+DOT_SIZE == x[z]) && (y[0] == y[z]))) {
                getMoveDirection("right");
            }else if(((z > 4) && (y[0]+DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("up");
            }else if(((z > 4) && (y[0]-DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("down");
        }
    }
        //getMoveDirection("right");
    }
    if((x[0] > apple_x)){
        for (int z = dots; z > 0; z--) {
            if (!((z > 4) && (x[0]-DOT_SIZE == x[z]) && (y[0] == y[z]))) {
                getMoveDirection("left");
            }else if(((z > 4) && (y[0]+DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("up");
            }else if(((z > 4) && (y[0]-DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("down");
        }
        //getMoveDirection("left");
    }
    }
    if (y[0] < apple_y) {
        for (int z = dots; z > 0; z--) {
            if (((z > 4) && (y[0]+DOT_SIZE == y[z]) && (x[0] == x[z]))) {
                getMoveDirection("up");
            }else if(!((z > 4) && (x[0]+DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("right");
            }else if(!((z > 4) && (x[0]-DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("left");
        }
        //getMoveDirection("down");
    }
    }
    if (y[0] > apple_y){
        for (int z = dots; z > 0; z--) {
            if (((z > 4) && (y[0]-DOT_SIZE == y[z]) && (x[0] == x[z]))) {
                getMoveDirection("down");
            }else if(!((z > 4) && (x[0]+DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("right");
            }else if(!((z > 4) && (x[0]-DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("left");
        }
        //getMoveDirection("up");
    }

    }
    if (x[0] < apple_x && leftDirection) {
        for (int z = dots; z > 0; z--) {
            if (!((z > 4) && (x[0]+DOT_SIZE == x[z]) && (y[0] == y[z]))) {
                getMoveDirection("right");
            }else if(((z > 4) && (y[0]+DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("up");
            }else if(((z > 4) && (y[0]-DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("down");
        }
    }
        //getMoveDirection("right");
    }
    if((x[0] > apple_x && rightDirection)){
        for (int z = dots; z > 0; z--) {
            if (!((z > 4) && (x[0]-DOT_SIZE == x[z]) && (y[0] == y[z]))) {
                getMoveDirection("left");
            }else if(((z > 4) && (y[0]+DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("up");
            }else if(((z > 4) && (y[0]-DOT_SIZE == y[z]) && (x[0] == x[z]))){
                getMoveDirection("down");
        }
        //getMoveDirection("left");
    }
    }
    if (y[0] < apple_y && !downDirection) {
        for (int z = dots; z > 0; z--) {
            if (!((z > 4) && (y[0]+DOT_SIZE == y[z]) && (x[0] == x[z]))) {
                getMoveDirection("down");
            }else if(!((z > 4) && (x[0]+DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("right");
            }else if(!((z > 4) && (x[0]-DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("left");
        }
        //getMoveDirection("down");
    }
    }
    if (y[0] > apple_y && !upDirection){
        for (int z = dots; z > 0; z--) {
            if (!((z > 4) && (y[0]-DOT_SIZE == y[z]) && (x[0] == x[z]))) {
                getMoveDirection("up");
            }else if(!((z > 4) && (x[0]+DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("right");
            }else if(!((z > 4) && (x[0]-DOT_SIZE == x[z]) && (y[0] == y[z]))){
                getMoveDirection("left");
        }
        //getMoveDirection("up");
    }

    }

}
void Snake::getMoveDirection(QString dir){
    if ((dir == "left") && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((dir == "right") && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((dir == "up") && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((dir == "down") && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
}

void Snake::stage1(){
    /* this stage will have no boundaries and will only terminate only if the snake eats
     * itself
     */
    QPainter qp(this);
    for (int z = dots; z > 0; z--) {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }
    if (y[0] >= B_HEIGHT) {
        // If colided(higher than) with the top
        getMoveDirection("up");
        qp.drawImage(x[0], -B_HEIGHT, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    }

    if (y[0] < 0) {
        getMoveDirection("down");
        qp.drawImage(x[0], B_HEIGHT, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    }

    if (x[0] >= B_WIDTH) {
        // If colided(past over) with the sides
        getMoveDirection("right");
        qp.drawImage(-B_WIDTH,y[0], apple);
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    }

    if (x[0] < 0) {
        getMoveDirection("left");
        qp.drawImage(B_WIDTH,y[0], apple);
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    }

if(!inGame) {
    // If inGame is false.
    // This means if the player has terminated the snake
    killTimer(timerId);
}
}
void Snake::stage2(){
    /* the stage which we current have
     */
    for (int z = dots; z > 0; z--) {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }
    if (y[0] >= B_HEIGHT) {
        // If colided(higher than) with the top
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        // If colided(past over) with the sides
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

if(!inGame) {
    // If inGame is false.
    // This means if the player has terminated the snake
    killTimer(timerId);
}
}

void Snake::stage3(){
    /* this stage will have two boundaries in the middle of the window
     */
}
void Snake::stage4(){
    /* this stage will have four boundaries by the corners
     */
}
